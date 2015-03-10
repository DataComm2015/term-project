#include "Server.h"

#include "Session.h"
#include "ReceiveProcess.h"
#include "SendProcess.h"

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

// < -- NEED MECHANISM FOR REMOVING STALE SESSIONS -- >

Networking::Server::Server()
{
	receiveProcess = new ReceiveProcess();
	sendProcess = new SendProcess();
}

Networking::Server::~Server()
{
	stopServer();
}

int Networking::Server::startServer(short port)
{
	sockaddr_in server;
	pthread_thread thread;
	
	// Create the Listening Socket
	if ((listeningSocket = socket(AF_INET, SOCK_STREAM, 0) == -1)
	{
		return 0;
	}
		
	// Bind an address to the socket
	bzero((char *)&server, sizeof(sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listeningSocket, (sockaddr *)&server, sizeof(server)) == -1)
	{
		return 0;
	}
	
	// Start Listening Thread
	pthread_create(&thread, Server::listeningThread, NULL, this);
}

int Networking::Server::stopServer()
{
	close(listeningSocket);
}

void *Networking::Server::listeningThread(void *server)
{
	Server *pThis = (Server*) server;
	int client_len, socket;
	sockaddr_in client;
	
	listen->server(pThis->listeningSocket, 5);
	socket = 0;
	
	while (socket != -1)
	{
		client_len= sizeof(client);
		if ((socket = accept (listeningSocket, (sockaddr *)&client, &client_len)) != -1)
		{
			// Create a new Session and add it to the Server's client list
			Session *session = new Session(socket, pThis->readProcess, pThis->sendProcess, pThis->entityMux);
			pThis->sessions.push_back(session);
		}
	}
}
