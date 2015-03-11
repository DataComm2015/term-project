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
    sockaddr_in server;
    pthread_t thread;

    // create the listening socket
    printf("server: create the listening socket\n");
    if((listeningSocket = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        return -1;
    }

    // bind an address to the socket
    printf("server: bind an address to the socket\n");
    bzero((char*) &server,sizeof(server));
    server.sin_family      = AF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listeningSocket,(sockaddr*) &server,sizeof(server)) == -1)
    {
        return -1;
    }

    // start listening thread
    printf("server: start listening thread\n");
    return pthread_create(&thread, 0, listeningThread, this);
}

/**
 * stops server, and closes all connections connected with the server.
 *
 * @return integer indicating the outcome of the operation
 */
int Server::stopServer()
{
    // close and remove all sessions
    for(auto session = sessions.begin(); session != sessions.end(); ++session)
    {
        delete (*session);
    }
    sessions.erase(sessions.begin(),sessions.end());

    // close the server socket
    return close(listeningSocket);
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
    listen(dis->listeningSocket, 5);

    // accept any connection requests, and create a session for each
    while(true)
    {
        printf("server: waiting for connections...\n");

        // accept the next connection & check for errors
        int socket;
        if((socket = accept(dis->listeningSocket,0,0)) == -1)
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
