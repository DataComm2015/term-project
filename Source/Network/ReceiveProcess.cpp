/*----------------------------------------------------------------------------------------------
-- DATE: February 21, 2015
--
-- Source File: ReceiveProcess.cpp
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER: Alex Lam, Calvin Rempel, Jeff Bayntun, Manuel Gonzales
--
-- INTERFACE:
-- ReceiveProcess();
--	~ReceiveProcess();
--	void addSession(Session *session);
--	void removeSession(Session *session);
--	void onMessageReceived(int socket, Message *message);
--	void runProcess();
--	void closeProcess();
--
--
-- NOTES: This file provides definitions for a ReceiveProcess object.
-----------------------------------------------------------------------------------------------*/
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
#include <sys/time.h>
#include <iostream>

#include <signal.h>
#include <vector>

#include "ancillary.h"
#include "Session.h"
#include <signal.h>

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		sig_handler
--
-- DATE:			February 21, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		void sig_handler()
--
-- RETURNS: 		void
--
-- NOTES:			calls onMessageReceived after the receive process signals the main process

							this will need the process -> game pipe
							//int p2[2];

-----------------------------------------------------------------------------------------------*/

void sig_handler(int signum)
{
	int socket;
	int messagelength;
	Message* message;
	read(p2[0], socket, sizeof(int));
	read(p2[0], messagelength, sizeof(int));
	read(p2[0], &message, messagelength);

	onMessageReceived(socket, message);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		ReceiveProcess
--
-- DATE:			February 21, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		Receive::ReceiveProcess()
--
-- RETURNS: 		void
--
-- NOTES:			Initalizes the ReceiveProcess object,
					creating the socket for file descriptors to be shared between processes,
					creates child process
-----------------------------------------------------------------------------------------------*/
Networking::ReceiveProcess::ReceiveProcess(int gamePipe[2])
{
	signal(SIGUSR1, sig_handler);

	p2 = gamePipe;

	if (pipe(gamePipe) < 0)
	{
		perror("pipe call");
	}

	/*-- Open the pipe ----*/
	if (pipe(p) < 0)
	{
		perror("pipe call");
	}

  if(socketpair(PF_UNIX, SOCK_STREAM, 0, ipcsock))
  {
	perror("socketpair");
  }
  else
  {
		//Create process
		pid = fork();
		if (pid == -1)
		{
			perror("Fork Failed!");
		}
		if (pid == 0)
		{
			close(ipcsock[0]);
			ReceiveProcess();
		}
		else
		{
			close(ipcsock[1]);
		}
  }
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		addSocket
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		void addSession(Session *session)
--	new_sd:			pointer to session to add
--
-- RETURNS: 		void
--
-----------------------------------------------------------------------------------------------*/
void Networking::ReceiveProcess::addSession(Session *session)
{
	unsigned int new_sd = session->getSocket();

	// Add Socket to Map on Parent Process
	sockets.insert(std::pair<int, int>(new_sd, new_sd));
	sessions.insert(std::pair<int, Session*>(new_sd, session));

	// Transfer Socket
	ancil_send_fd(ipcsock[0], new_sd);

	// Create Message to Send on Pipe
	ReceiveMessage message;
	message.type = ADD_SOCKET;
	message.socket_id = new_sd;

	// Inform child process of new Socket
	write(p[1], &message, 1);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		removeSession
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam, Jeff Bayntun
--
-- INTERFACE:		void removeSession(Session *session)
--	session:		pointer to the session to remove
--
-- RETURNS: 		void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void Networking::ReceiveProcess::removeSession(Session *session)
{
	unsigned int sd = session->getSocket();

	// Remove Socket from Map on Parent Process
	sessions.erase(sd);
	sockets.erase(sd);
	close(sd);

	// Create Message to Send on Pipe
	ReceiveMessage message;
	message.type = REMOVE_SOCKET;
	message.socket_id = sd;

	// Inform child process of new Socket
	write(p[1], &message, 1);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		onmessageReceived
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		void onMessageReceived(int socket, Message *message)
--
-- RETURNS: 		void
--
-- NOTES:			Calls the "onMessageReceived" method of the Session that received data.
-----------------------------------------------------------------------------------------------*/
void Networking::ReceiveProcess::onMessageReceived(int socket, Message *message)
{
	Session *session = sessions[socket];
	session->onMessageReceived(message);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		closeProcess
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		void Receive::closeProcess()
--
-- RETURNS: 		void
--
-- NOTES:			Writes close signal to the receive process
-----------------------------------------------------------------------------------------------*/
void Networking::ReceiveProcess::closeProcess()
{
	ReceiveMessage message;
	message.type = SHUTDOWN;
	message.socket_id = 0;

	write(p[1], &message, sizeof(ReceiveMessage));
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		runProcess
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam, Jeff Bayntun
--
-- INTERFACE:		void Receive::runProcess()
--
-- RETURNS: 		void
--
-- NOTES:			The main point of this program,
					This process starts by initalizing it's set of file descriptors to monitor for select
					Then it monitors the pipe between this process and the main for any messages
					and checks for any tcp data coming in.
-----------------------------------------------------------------------------------------------*/
void Networking::ReceiveProcess::runProcess()
{
	fd_set readfds;
	int max_sd = 0;
	int n;
	int clientSockets[25];
	char buf[BUFLEN];
	int activity;
	char* bp;
	int bytes_to_read;

	using std::map;
	using std::cerr;
	using std::endl;
	using std::cout;

	while (1)
	{
		// DON'T THINK THIS TOP PART IS NEEDED ANYMORE...
		FD_ZERO(&readfds);
		FD_SET(p[0], &readfds);
		max_sd = p[0];
		for(std::map<int, int>::iterator it = sockets.begin(); it != sockets.end(); ++it)
		{
			FD_SET(it->first, &readfds);
			if(it->first > max_sd)
			{
				max_sd = it->first;
			}
		}
		//

		// Block the Process until one of the sockets (or the pipe) has data to read
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		// If an error occurred, close all sockets and exit the process
		if(activity == -1)
		{
			map<int,int>::iterator it;
			for (it = sockets.begin(); it != sockets.end(); ++it)
			{
				close(it->first);
			}

			// Print the error
			cerr << errno << endl;
			exit(1);
		}

		//Wait for activity on either the pipe or one of the sockets
		cout << "Number of activity detected: " << activity << endl;
		if (FD_ISSET(p[0], &readfds))//If it is the PIPE that has activity
		{
			char temp_message[NETWORK_MESSAGE_SIZE];
			ReceiveMessage* parent_messages;

			read(p[0], temp_message, NETWORK_MESSAGE_SIZE);
			parent_messages = (ReceiveMessage*)temp_message;


			// Shutdown the Process
			if(parent_messages->type == ReceiveMessageType::SHUTDOWN)
			{
				// < -- CLOSE SOCKET HANDLES HERE! -- >
				exit(0);
			}
			// Add a Socket From the Parent Process
			else if (parent_messages->type == ReceiveMessageType::ADD_SOCKET)
			{
				int new_socket;
				cout << "Check for new connections" << endl;
				ancil_recv_fd(ipcsock[1], &new_socket);
				cout << "New connection on socket: " << new_socket << endl;

				FD_SET(new_socket, &readfds); //Sets socket for 'select' monitor

				// Add socket to map where socket id on original process is used as the key
				sockets.insert(std::pair<int, int>(parent_messages->socket_id, new_socket));

				if(new_socket > max_sd)
				{
					max_sd = new_socket;
				}
			}

			// Remove a specified Socket from the fd_set
			else if (parent_messages->type == ReceiveMessageType::REMOVE_SOCKET)
			{
				int socket_id = sockets[parent_messages->socket_id];
				FD_CLR(socket_id, &readfds);
				close(socket_id);
				sockets.erase(parent_messages->socket_id);
			}
		}

		// Check all clients to see if they have data available
		for(map<int, int>::iterator it = sockets.begin(); it != sockets.end(); ++it)
		{
			if (FD_ISSET(it->first, &readfds))
			{
				//Read tcp data
				bp = buf;
				bytes_to_read = BUFLEN;
				n = 0;

				while ((n = recv (it->first, bp, bytes_to_read, 0)) < BUFLEN)
				{
					bp += n;
					bytes_to_read -= n;
				}

				// < -- SEND MESSAGE BACK TO MAIN PROCESS HERE -- >
				write(p2[1], it->first, sizeof(int));
				int messageReadLength = sizeof(buf);
				write(p2[1], messageReadLength, sizeof(int));
				write(p2[1], buf, messageReadLength);
				signal(SIGUSR1, sig_handler);

				ReceiveMessage message;
				message.type = MESSAGE_AVAILABLE;
				message.socket_id =
				printf ("Received: %s\n", buf);
				fflush(stdout);
			}
		}
	}
}
