#include "Server.h"
#include "Session.h"
#include "net_helper.h"
#include "select_helper.h"
#include "Message.h"

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <vector>

// #define DEBUG

using namespace Networking;

// forward declarations
static void fatal_error(const char* errstr);

/**
 * constructs a new {Server}.
 */
Server::Server()
{
    svrSock = 0;
}

/**
 * Clean up the Server on destruction.
 */
Server::~Server()
{
    stopServer();
}

/**
 * initializes the server to listen for incoming connections on the
 *   given port
 *
 * @param  port to connect to
 *
 * @return integer indicating the outcome of the operation
 */
int Server::startServer(short port)
{
    // return immediately if the server is already started
    if(svrSock != 0)
    {
        return 0;
    }

    // create the control pipe
    if(pipe(ctrlPipe) == -1)
    {
        fatal_error("failed to create the control pipe");
    }

    // create the listening socket
    svrSock = make_tcp_server_socket(port);

    // start the server thread
    return pthread_create(&serverThread,0,serverRoutine,this);
}

/**
 * stops server, and closes all connections connected with the server.
 *
 * @return 0 upon success; -1 on failure. check errno for details.
 */
int Server::stopServer()
{
    // return immediately if the server is already stopped
    if(svrSock == 0)
    {
        return 0;
    }

    // close the control pipe which terminates the server thread
    close(ctrlPipe[1]);

    // close the server socket
    pthread_join(serverThread,0);
    int ret = close(svrSock);

    // set svrSock to 0, so we know it's closed
    svrSock = 0;

    return ret;
}

void Server::onConnect(Session* session)
{
}

void Server::onMessage(Session* session, char* data, int len)
{
}

void Server::onDisconnect(Session* session, int remote)
{
}

void Server::onConnect(int socket)
{
    #ifdef DEBUG
    printf("server: socket %d connected\n",socket);
    #endif
    sessions[socket] = new Session(socket);
    onConnect(sessions[socket]);
}

void Server::onMessage(int socket, char* data, int len)
{
    #ifdef DEBUG
    printf("server: socket %d: ",socket);
    for(int i = 0; i < len; ++i)
    {
        printf("%c",data[i]);
    }
    printf("\n");
    #endif
    // packet comes in order of: int type, int length, array data
    Message msg;
    msg.type = *(((int*)data)+0);
    msg.len  = *(((int*)data)+1);
    msg.data = ((int*)data)+2;
    onMessage(sessions[socket],data,len);
    sessions[socket]->onMessage(&msg);
}

void Server::onDisconnect(int socket, int remote)
{
    #ifdef DEBUG
    printf("server: socket %d disconnected by %s host\n",socket,remote?"remote":"local");
    #endif
    onDisconnect(sessions[socket],remote);
    sessions[socket]->onDisconnect(remote);
    sessions[socket]->markForDeletion();
    sessions.erase(socket);
}

/**
 * function run on a thread. it polls the server socket, accepting connections.
 *
 * @param params thread parameters; points to the calling server instance.
 */
void* Server::serverRoutine(void* params)
{
    // parse thread parameters
    Server* dis = (Server*) params;

    int terminateThread = 0;

    // set up the socket set & client list
    Files files;
    files_init(&files);

    // add the server socket and control pipe to the select set
    files_add_file(&files,dis->svrSock);
    files_add_file(&files,dis->ctrlPipe[0]);

    // accept any connection requests, and create a session for each
    while(!terminateThread)
    {
        // wait for an event on any socket to occur
        if(files_select(&files) == -1)
        {
            fatal_error("failed on select");
        }

        // loop through sockets, and handle them
        for(auto socketIt = files.fdSet.begin(); socketIt != files.fdSet.end();
            ++socketIt)
        {
            int curSock = *socketIt;

            // if this socket doesn't have any activity, move on to next socket
            if(!FD_ISSET(curSock,&files.selectFds))
            {
                continue;
            }

            // handle socket activity depending on which socket it is
            if(curSock == dis->svrSock)
            {
                /*
                 * this is the server socket, try to accept a connection.
                 *
                 * if the operation fails, end the server thread, because when
                 *   accept fails, it means that the server socket is closed.
                 *
                 * if accept succeeds, add it to the select set, and continue
                 *   looping...
                 */

                // accept the connection
                int newSock;
                if((newSock = accept(dis->svrSock,0,0)) == -1)
                {
                    // accept failed; server socket closed, terminate thread
                    terminateThread = 1;
                }
                else
                {
                    // accept success; add to select set, and call callback
                    files_add_file(&files,newSock);
                    dis->onConnect(newSock);
                }
            }
            else if(curSock == dis->ctrlPipe[0])
            {
                /*
                 * this is the control pipe. whenever anything happens on the
                 *   control pipe, it means it's time for the server to
                 *   shutdown; break out of the server loop.
                 */
                 close(dis->ctrlPipe[0]);
                 terminateThread = 1;
            }
            else
            {
                /*
                 * this is the client socket; try to read from the socket
                 *
                 * if read fails, it means that the socket is closed, remove it
                 *   from the select set, call a callback, and continue looping.
                 *
                 * if read succeeds, read until socket is empty, and call
                 *   callback, then continue looping.
                 */

                // read from socket
                int result;
                int msglen;
                if((result = read_file(curSock,&msglen,sizeof(msglen))) == 0)
                {
                    // socket closed; remove from select set, and call callback
                    files_rm_file(&files,curSock);
                    dis->onDisconnect(curSock,(close(curSock) == 0));
                }
                else
                {
                    // socket read; read more from socket, and call callback
                    char* buffer = (char*) malloc(msglen);
                    read_file(curSock,buffer,msglen);
                    dis->onMessage(curSock,buffer,msglen);
                    free(buffer);
                }
                break;
            }
        }
    }

    // close all sockets before terminating
    for(auto socketIt = files.fdSet.begin(); socketIt != files.fdSet.end();
        ++socketIt)
    {
        int curSock = *socketIt;
        close(curSock);
        if(curSock != dis->svrSock && curSock != dis->ctrlPipe[0])
        {
            dis->onDisconnect(curSock,0);
        }
    }

    return 0;
}

static void fatal_error(const char* errstr)
{
    perror(errstr);
    exit(errno);
}
