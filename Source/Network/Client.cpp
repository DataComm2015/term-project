#include "Client.h"
#include "Session.h"
#include "net_helper.h"
#include "select_helper.h"
#include "Message.h"

using namespace Networking;

// forward declarations
static void fatal_error(const char* errstr);

Client::Client()
{
    // create the control pipe
    if(pipe(ctrlPipe) == -1)
    {
        fatal_error("failed to create the control pipe");
    }

    // start the client thread
    pthread_create(&clientThread,0,clientRoutine,this);
}

Client::~Client()
{
    // close the control pipe which terminates the client thread
    close(ctrlPipe[1]);

    // wait for the client thread to die before dying
    pthread_join(clientThread,0);
}

int Client::connect(char* remoteName, short remotePort)
{
    // connect to remote host
    int socket = make_tcp_client_socket(remoteName,0,remotePort,0);

    if(socket != -1)
    {
        // communicate to client thread that a new session is connected
        write(ctrlPipe[1],&socket,sizeof(socket));
    }

    // return 0 upon success; -1 otherwise
    return socket;
}

void Client::onConnect(int socket)
{
#ifdef DEBUG
    printf("client: socket %d connected\n",socket);
#endif
    sessions[socket] = new Session(socket);
}

void Client::onMessage(int socket, char* data, int len)
{
#ifdef DEBUG
    printf("client: socket %d: ",socket);
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
    sessions[socket]->onMessage(&msg);
}

void Client::onDisconnect(int socket, int remote)
{
#ifdef DEBUG
    printf("client: socket %d disconnected by %s host\n",socket,remote?"remote":"local");
#endif
    sessions[socket]->onDisconnect(remote);
    sessions[socket]->markForDeletion();
    sessions.erase(socket);
}

void* Client::clientRoutine(void* params)
{
    // parse thread parameters
    Client* dis = (Client*) params;

    // used to break the while loop
    int terminateThread = 0;

    // set up the socket set & client list
    Files files;
    files_init(&files);

    // add the server socket and control pipe to the select set
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
            if(curSock == dis->ctrlPipe[0])
            {
                /*
                 * this is the control pipe. try to read from the control pipe.
                 *
                 * if the control pipe is closed, the client is being deleted;
                 *   this client thread should terminate.
                 *
                 * if the control pipe is read, that means that a new socket is
                 *   now connected, and needs to be added to the selection set.
                 */

                int socket;
                if(read_file(dis->ctrlPipe[0],&socket,sizeof(socket)) == 0)
                {
                    // pipe closed; the client is being deleted, thread should
                    // terminate
                    close(dis->ctrlPipe[0]);
                    terminateThread = 1;
                }
                else
                {
                    // pipe read; a new socket is being added to the select set
                    files_add_file(&files,socket);
                    dis->onConnect(socket);
                }
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
        if(curSock != dis->ctrlPipe[0])
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
