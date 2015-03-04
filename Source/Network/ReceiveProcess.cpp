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

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		Receive
--
-- DATE:			February 21, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		Receive::Receive()
--
-- RETURNS: 		void
--
-- NOTES:			Initalizes the ReceiveProcess object,
					creating the socket for file descriptors to be shared between processes,
					creates child process
-----------------------------------------------------------------------------------------------*/
Networking::ReceiveProcess::ReceiveProcess()
{
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
-- INTERFACE:		void Receive::addSocket(int new_sd)
--	new_sd:			The new socket to be added
--
-- RETURNS: 		void
--
-- NOTES:			Takes the new socket and adds it to the receive process
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
	message.socket = new_sd;
	
	// Inform child process of new Socket
	write(p[1], &message, 1);
}

// COMMENT HEADER FOR removeSocket
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
	message.socket = sd;
	
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
	message.socket = 0;
	
	write(p[1], &message, sizeof(ReceiveMessage));
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		ReceiveProcess
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		void Receive::ReceiveProcess()
--
-- RETURNS: 		void
--
-- NOTES:			The main point of this program,
					This process starts by initalizing it's set of file descriptors to monitor for select
					Then it monitors the pipe between this process and the main for any messages
					and checks for any tcp data coming in.
-----------------------------------------------------------------------------------------------*/
void Networking::ReceiveProcess::ReceiveProcess()
{


	//   **  	< -- CHANGE ALL ITERATION OVER clientList TO ITERATE OVER sockets MAP!!! -- > **


	fd_set readfds;
	int max_sd = 0;
	int n;
	int clientSockets[25];
	char buf[BUFLEN];
	int activity;
	char* bp;
	int bytes_to_read;

	while (1)
	{
		// DON'T THINK THIS TOP PART IS NEEDED ANYMORE...
		FD_ZERO(&readfds);
		FD_SET(p[0], &readfds);
		max_sd = p[0];
		for(vector<int>::iterator it = clientList.begin(); it != clientList.end(); ++it)
		{
			FD_SET(*it, &readfds);
			if(*it > max_sd)
			{
				max_sd = *it;
			}	
		}
		//

		// Block the Process until one of the sockets (or the pipe) has data to read
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		
		// If an error occurred, close all sockets and exit the process
		if(activity == -1)
		{
			vector<int>::iterator it;
			for (it = clientList.begin(); it != clientList.end(); ++it)
			{
				close(*it);
			}
			
			// Print the error
			cerr << errno << endl;
			exit(1);
		}

		//Wait for activity on either the pipe or one of the sockets
		cout << "Number of activity detected: " << activity << endl;
		if (FD_ISSET(p[0], &readfds))//If it is the PIPE that has activity
		{
			int parent_messages;
			read(p[0], &parent_messages, MSGSIZE);
			
			// Shutdown the Process
			if(parent_messages == ReceiveMessageType::SHUTDOWN)
			{
				// < -- CLOSE SOCKET HANDLES HERE! -- >
				exit(0);
			}
			// Add a Socket From the Parent Process
			else if (parent_messages == ReceiveMessageType::ADD_SOCKET)
			{
				int new_socket;
				cout << "Check for new connections" << endl;
				ancil_recv_fd(ipcsock[1], &new_socket);
				cout << "New connection on socket: " << new_socket << endl;

				FD_SET(new_socket, &readfds); //Sets socket for 'select' monitor
				
				// Add socket to map where socket id on original process is used as the key
				sockets.insert(std::pair<int, int>(parent_messages.socket_id, new_socket));

				if(new_socket > max_sd)
				{
					max_sd = new_socket;
				}
			}
			
			// Remove a specified Socket from the fd_set
			else if (parent_messages == ReceiveMessageType::REMOVE_SOCKET)
			{
				int socket_id = sockets[parent_messages.socket_id];
				FD_CLR(socket_id, &readfds);
				close(socket_id);
				sockets.erase(parent_messages.socket_id);
			}
		}
		
		// Check all clients to see if they have data available
		for(vector<int>::iterator it = clientList.begin(); it != clientList.end(); ++it)
		{
			if (FD_ISSET(*it, &readfds))
			{
				//Read tcp data
				bp = buf;
				bytes_to_read = BUFLEN;
				n = 0;
				
				while ((n = recv (*it, bp, bytes_to_read, 0)) < BUFLEN)
				{
					bp += n;
					bytes_to_read -= n;
				}
				
				// < -- SEND MESSAGE BACK TO MAIN PROCESS HERE -- >
				ReceiveMessage message;
				message.type = MESSAGE_RECEIVED;
				message.socket_id = 
				printf ("Received: %s\n", buf);
				fflush(stdout);
			}
		}
	}
}
