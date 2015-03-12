#include "Server.h"
#include "Session.h"
#include "ReceiveProcess.h"
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
// < -- NEED MECHANISM FOR REMOVING STALE SESSIONS -- >

using namespace Networking;

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

    // create the listening socket
    svrSock = make_tcp_server_socket(port);

    // start the server thread
    return pthread_create(&serverThread, 0, serverRoutine, this);
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

    // close the server socket, which also terminates the server thread
    int ret = close(svrSock);

    // set svrSock to 0, so we know it's closed
    svrSock = 0;

    return ret;
}

void Server::onConnect(int socket)
{
#ifdef DEBUG
    printf("server: socket %d connected\n",socket);
#endif
    // sessions[socket] = new Session();
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
    // Message msg;
    // msg.type = *(int*)data;
    // msg.data = ((int*)data)+1;
    // msg.len  = len-sizeof(int);
    // sessions[socket]->onMessageReceived(&msg);
}

void Server::onDisconnect(int socket, int remote)
{
#ifdef DEBUG
    printf("server: socket %d disconnected by %s host\n",socket,remote?"remote":"local");
#endif
    // sessions[socket]->onDisconnect(remote);
    // free(sessions[socket]);
    // sessions.erase(socket);
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

    // add the server socket to the select set
    files_add_file(&files,serverSocket);

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
            if(!FD_ISSET(curSock,&files.selectFds)
            {
                continue;
            }

            // handle socket activity depending on which socket it is
            switch(curSock)
            {
            case dis->svrSock;  // server socket
                // accept the connection
                int newSock;
                if((newSock = accept(svrSock,0,0)) == -1)
                {
                    // accept failed; server socket closed, terminate thread
                    terminateThread = 1;
                }
                else
                {
                    // accept success; add to select set, and call callback
                    files_add_file(files,newSocket);
                    dis->onConnect(newSock);
                }
                break;
            default:            // client socket
                // read from socket
                int result;
                int msglen
                if((result = read_socket(curSock,&msglen,sizeof(msglen))) == 0)
                {
                    // socket closed; remove from select set, and call callback
                    files_rm_file(files,curSock);
                    close(selectedSocket);
                    dis->onDisconnect(curSock,1); // TODO: figure out if it's remote or not
                }
                else
                {
                    // socket read; read more from socket, and call callback
                    char* buffer = (char*) malloc(msglen);
                    read_socket(curSock,buffer,msglen);
                    dis->onMessage(curSock,buffer,msglen);
                    free(buffer);
                }
                break;
            }
        }
    }

    return 0;
}
