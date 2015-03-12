#include "Server.h"
#include "ReceiveProcess.h"

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
#include <vector>

// < -- NEED MECHANISM FOR REMOVING STALE SESSIONS -- >

using namespace Networking;

/**
 * constructs a new {Server}.
 */
Server::Server()
{
    svrSock = 0;
    receiveProcess = new ReceiveProcess(this,onSocketActivity);
}

/**
 * Clean up the Server on destruction.
 */
Server::~Server()
{
    printf("Server::~Server()\n");
    delete receiveProcess;
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
    if(svrSock != 0)
    {
        return 0;
    }

    sockaddr_in server;
    pthread_t thread;

    // create the listening socket
    if((svrSock = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("failed to create the listening socket");
        return -1;
    }

    // set sock opt to reuse address
    int arg = 1;
    if(setsockopt(svrSock,SOL_SOCKET,SO_REUSEADDR,&arg,sizeof(arg)) == -1)
    {
        perror("failed to set sock opt to reuse address");
        return -1;
    }

    // bind an address to the socket
    bzero((char*) &server,sizeof(server));
    server.sin_family      = AF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(svrSock,(sockaddr*) &server,sizeof(server)) == -1)
    {
        perror("failed to bind an address to the socket");
        return -1;
    }

    // start listening thread
    return pthread_create(&thread, 0, listeningRoutine, this);
}

/**
 * stops server, and closes all connections connected with the server.
 *
 * @return 0 upon success; -1 on failure. check errno for details.
 */
int Server::stopServer()
{
    if(svrSock == 0)
    {
        return 0;
    }

    // // close and remove all sessions
    // for(auto session = sessions.begin(); session != sessions.end(); ++session)
    // {
    //     delete (*session);
    // }
    // sessions.erase(sessions.begin(),sessions.end());

    // close the server socket
    int ret = close(svrSock);
    svrSock = 0;

    return ret;
}

void Server::onConnect(int socket)
{
    printf("server: socket %d connected\n",socket);
}

void Server::onMessage(int socket, char* data, int len)
{
    printf("server: socket %d: ",socket);
    for(int i = 0; i < len; ++i)
    {
        printf("%c",data[i]);
    }
    printf("\n");
}

void Server::onDisconnect(int socket, int remote)
{
    printf("server: socket %d disconnected by %s host\n",socket,remote?"remote":"local");
}

/**
 * function run on a thread. it polls the server socket, accepting connections.
 *
 * @param params thread parameters; points to the calling server instance.
 */
void* Server::listeningRoutine(void* params)
{
    // parse thread parameters
    Server* dis = (Server*) params;

    // start listening on the server socket
    listen(dis->svrSock,5);

    // accept any connection requests, and create a session for each
    while(true)
    {
        #ifdef DEBUG
        printf("server: waiting for connections...\n");
        #endif

        // accept the next connection & check for errors
        int socket;
        if((socket = accept(dis->svrSock,0,0)) == -1)
        {
            perror("failed to accept connection\n");
            break;
        }

        // create a session for the new connection
        dis->receiveProcess->addSocket(socket);
        dis->onConnect(socket);
    }

    return 0;
}

void Server::onSocketActivity(void* params, int socket)
{
    // parse callback parameters
    Server* dis = (Server*) params;

    // read from socket
    int msglen;
    int result = read(socket,&msglen,sizeof(msglen));

    // remove socket if the socket encounters an error, or is closed
    if(result == 0 || result == -1)
    {
        dis->onDisconnect(socket,1);
        dis->receiveProcess->removeSocket(socket);
        close(socket);
    }
    else
    {
        void* buffer = malloc(msglen);
        read(socket,buffer,msglen);
        dis->onMessage(socket,(char*) buffer,msglen);
        free(buffer);
    }
}
