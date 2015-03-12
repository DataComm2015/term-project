#include "Server.h"
#include "Session.h"

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
    if(svrSock != 0)
    {
        return 0;
    }

    sockaddr_in server;
    pthread_t thread;

    // create the listening socket
    printf("server: create the listening socket\n");
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
    printf("server: bind an address to the socket\n");
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
    printf("server: start listening thread\n");
    return pthread_create(&thread, 0, listeningThread, this);
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

    // close and remove all sessions
    for(auto session = sessions.begin(); session != sessions.end(); ++session)
    {
        delete (*session);
    }
    sessions.erase(sessions.begin(),sessions.end());

    // close the server socket
    int ret = close(svrSock);
    svrSock = 0;

    return ret;
}

/**
 * function to be overridden by subclasses
 *
 * @param  session
 */
void Server::onConnect(Session* session)
{
    printf("server: session %p connected\n",session);
}

/**
 * function run on a thread. it polls the server socket, accepting connections.
 *
 * @param params thread parameters; points to the calling server instance.
 */
void* Server::listeningThread(void* params)
{
    // parse thread parameters
    Server* dis = (Server*) params;

    // start listening on the server socket
    listen(dis->svrSock,5);

    // accept any connection requests, and create a session for each
    while(true)
    {
        printf("server: waiting for connections...\n");

        // accept the next connection & check for errors
        int socket;
        if((socket = accept(dis->svrSock,0,0)) == -1)
        {
            printf("server: accept fails...\n");
            break;
        }

        // create a session for the new connection
        Session* session = new Session(socket);
        dis->sessions.push_back(session);
        dis->onConnect(session);
    }

    return 0;
}
