/*----------------------------------------------------------------------------------------------
-- DATE: 		February 21, 2015
--
-- Source File:	ReceiveProcess.cpp
--
-- REVISIONS: 	(Date and Description)
--
-- DESIGNER:	Alex Lam
--
-- PROGRAMMER:	Alex Lam
--				Calvin Rempel
--
--
-- INTERFACE:
--
--
-- NOTES: 	This is the receive process that is to be later implemented into the rest of the
			networking code.

			Since midterms are coming up, I am putting this aside for a bit and will come back
			to finish it later!
			The main function currently tries to imitate what the rest of the networking code do.

			What works:
				You can create a ReceiveProcess function
				You can add MULTIPLE sockets for it to listen to ( special thanks to Calvin Rempel for spending 6 
					on passing file descriptors between processes with me)
				The select statement is able to check if there is either
					new TCP data to be read
					new sockets that need to be added
				Ctrl+C will terminate the sockets(kinda) and terminate the process

			What doesn't work:
				The address sometimes doesn't get unbind when the program terminates.

			What needs to be added:
				Ability to remove sockets when client disconnects.

			This has been tested with Aman's tcp_clnt code and it seems to work.

			There is quite a bit of cleaning up to do but I want this code on the git repo so
			others can see how to get file descriptors can to be shared between processes.
-----------------------------------------------------------------------------------------------*/
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

using namespace std;

#define SERVER_TCP_PORT 7002	// Default port
#define BUFLEN	80		//Buffer length
#define MSGSIZE	4

struct my_msg {
	long mtype;
	char msocket;
};

vector<int> socketlist;

void sig_handler(int sig);

class Receive {
	int p[2];
	vector<int> clientList;
	int ipcsock[2];
	public:
		Receive();
		void ReceiveProcess();
		void addSocket(int);
		void closeProcess();
};

/*
	Main Process
	Creates process to handle new clients connecting
*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		main
--
-- DATE:			February 21, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		int main (int argc, char **argv)
--	argc:			argument count
--	agrv:			argvument array
--
-- RETURNS: 		int for success fail
--
-- NOTES:			Drives the testing for receive process
-----------------------------------------------------------------------------------------------*/
int main (int argc, char **argv)
{
	int	n;
	int	sd, new_sd, port;
	unsigned int client_len;
	struct	sockaddr_in server, client;

	signal(SIGINT, sig_handler);

	switch(argc)
	{
		case 1:
			port = SERVER_TCP_PORT;	// Use the default port
		break;
		case 2:
			port = atoi(argv[1]);	// Get user specified port
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}

	// Create a stream socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

	// Bind an address to the socket
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

	int optval = 1;
	
	if( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 )
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind name to socket");
		exit(1);
	}

	// Start new receive
	Receive rp;

	// Listen for connections
	// queue up to 5 connect requests
	listen(sd, 5);
	cout << "Listening on socket: " << sd << endl;
	socketlist.push_back (sd);

	while(1)
	{
		client_len= sizeof(client);
		if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1)
		{
			cerr << "Can't accept client" << endl;
			break;
		}
		else
		{
			socketlist.push_back (new_sd);
			cout << "New socket connection  " << new_sd << endl;
			rp.addSocket(new_sd);
		}
	}
	rp.closeProcess();

	printf(" Remote Address:  %s\n", inet_ntoa(client.sin_addr));
	
	return(0);
}

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
Receive::Receive()
{
	/*-- Open the pipe ----*/
	if (pipe(p) < 0)
	{
		perror("pipe call");
		exit(1);
	}

    if(socketpair(PF_UNIX, SOCK_STREAM, 0, ipcsock)) {
	perror("socketpair");
	exit(1);
    } else {
	printf("Established socket pair: (%d, %d)\n", ipcsock[0], ipcsock[1]);
    }

	//Create process
	pid_t childpid;
	childpid = fork();
	if (childpid == -1) 
	{
		perror("Fork Failed!");
	}
	if (childpid == 0)
	{
		close(ipcsock[0]);
		ReceiveProcess();
	}
	else
	{
		close(ipcsock[1]);
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
void Receive::addSocket(int new_sd)
{
	cout << "New socket added: " << new_sd << endl;
	ancil_send_fd(ipcsock[0], new_sd);
	int one = 1;
	write(p[1], &one, MSGSIZE);
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
void Receive::closeProcess()
{
	cout << "Send message written" << endl;
	int negone = -1;
	write(p[1], &negone, MSGSIZE);
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
void Receive::ReceiveProcess()
{
	fd_set readfds;
	int max_sd = 0;
	int n;
	int clientSockets[25];
	char buf[BUFLEN];
	int activity;
	char* bp;
	int bytes_to_read;

	cout <<"Receive Process Started" << endl;
	while (1)
	{
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

		cout << "Selecting" << endl;

		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		if(activity == -1)
		{
			vector<int>::iterator it;
			for (it = clientList.begin(); it != clientList.end(); ++it)
			{
				cout << "Closing socket: " << *it << endl;
				close(*it);
			}
			cerr << errno << endl;
		}

		//Wait for activity on either the pipe or one of the sockets
		cout << "Number of activity detected: " << activity << endl;
		if (FD_ISSET(p[0], &readfds))//If it is the PIPE that has activity
		{
			int parent_messages;
			read(p[0], &parent_messages, MSGSIZE);
			if(parent_messages == -1)
			{
				cout << "Exiting Process" << endl;
				return;
			}

			int new_socket;
			cout << "Check for new connections" << endl;
			ancil_recv_fd(ipcsock[1], &new_socket);
			cout << "New connection on socket: " << new_socket << endl;

			FD_SET(new_socket, &readfds); //Sets socket for 'select' monitor
			clientList.push_back(new_socket); //Add new socket to list of sockets

			if(new_socket > max_sd)
			{
				max_sd = new_socket;
			}
		}
		else
		{
			for(vector<int>::iterator it = clientList.begin(); it != clientList.end(); ++it)//If it was activity on one of the ports
			{
				if (FD_ISSET(*it, &readfds))
				{
					//Read tcp data
					cout << "Check for new Data on socket " << *it << endl;
					bp = buf;
					bytes_to_read = BUFLEN;
					n = 0;
					while ((n = recv (*it, bp, bytes_to_read, 0)) < BUFLEN)
					{
						cout <<" i am stuck" << endl;
						bp += n;
						bytes_to_read -= n;
					}
					printf ("Received: %s\n", buf);
					fflush(stdout);
				}
			}
		}
	}
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		sig_handler
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Alex Lam
--
-- PROGRAMMER:		Alex Lam
--
-- INTERFACE:		void sig_handler(int sig)
--	sig:			Don't worry about this
--
-- RETURNS: 		void
--
-- NOTES:			Closes all the sockets that were open.
-----------------------------------------------------------------------------------------------*/
void sig_handler(int sig)
{
	vector<int>::iterator it;
	for (it = socketlist.begin(); it != socketlist.end(); ++it)
	{
		cout << "Closing socket: " << *it << endl;
		close(*it);
	}
}
