#include "Server.h"

// #include "Session.h"
// #include "ReceiveProcess.h"
// #include "SendProcess.h"

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

Networking::Server::Server()
{
    // receiveProc = new ReceiveProcess();
    // sendProc = new SendProcess();
}

Networking::Server::~Server()
{
    stopServer();
}

/**
 * returns 0 upon success, -1 on network error, and an error number on thread
 *   creation error.
 */
int Networking::Server::startServer(short port)
{
    sockaddr_in server;
    pthread_t thread;

    // create the listening socket
    printf("create the listening socket\n");
    if((listeningSocket = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        return -1;
    }

    // bind an address to the socket
    printf("bind an address to the socket\n");
    bzero((char*) &server,sizeof(server));
    server.sin_family      = AF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listeningSocket,(sockaddr*) &server,sizeof(server)) == -1)
    {
        return -1;
    }

    // start listening thread
    printf("start listening thread\n");
    return pthread_create(&thread, 0, listeningThread, this);
}

int Networking::Server::stopServer()
{
    return close(listeningSocket);
}

void Networking::Server::onConnect(Session* session)
{
    printf("session %p connected\n",session);
}

void* Networking::Server::listeningThread(void* params)
{
    using Networking::Server;

    // parse thread parameters
    Server* dis = (Server*) params;

    // start listening on the server socket
    listen(dis->listeningSocket, 5);

    // accept any connection requests, and create a session for each
    while(true)
    {
        printf("waiting for connections...\n");

        // accept the next connection & check for errors
        int socket;
        if((socket = accept(dis->listeningSocket,0,0)) == -1)
        {
            printf("accept fails...\n");
            break;
        }
        // Session* session = new Session(socket,readProc,sendProc,entityMux);
        // sessions.push_back(session);
        dis->onConnect(0);
    }

    return 0;
}
