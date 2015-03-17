/*----------------------------------------------------------------------------------------------
-- DATE: February 28, 2015
-- 
-- Source File: SendProcess.cpp
-- 
-- REVISIONS: (Date and Description)
-- 
-- DESIGNER: Manuel Gonzales
-- 
-- PROGRAMMER: Manuel Gonzales
-- 
-- 
-- INTERFACE:
-- 
-- 
-- NOTES: Starting version of the send process. To keep it short the sender reads 3 pieces of information from the message queue, the first one is the socket descriptor followed by the data size and the data. It will read these form the queue and then verify that the data received matches the size, once everyhting is correct it will send the data through the socket. WE ARE EXPECTING THIS PROCESS TO BE FAST ENOUGH TO MANAGE SENDING INFO TO SEVERAL CLIENTS.
-----------------------------------------------------------------------------------------------*/
/*
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include "ancillary.h" /it looks that file descriptors can be passed through message queues w/o suing this library/
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/socket.h>
#include <time.h> 

using namespace std;

#define DEFAULT_PORT 7000 // Default port
#define DEFAULT_TYPE 1	// Default type
#define MKEY	150  	//Default Message Queue Key
#define BUFLEN	1024	//Buffer length

struct Message
{
		long mesg_type;
		int mesg_len;
		char mesg_data[BUFLEN];
};

void terminateP(int sign);
void mqstat_print (key_t mkey, int mqid, struct msqid_ds *mstat);
int read_message( int qid, long type, struct Message *message);

class Send 
{
	private:
	
	int qid;
	long type;
	struct Message *message;
	int socket;
	int data_size;
	char data[BUFLEN];
	int port;

	public:
	
	Send(int qid_s, long type_s, struct Message *message_s, int port_s);
	int ReadQueue();
	int Verify();
	int SendData();
};

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: main
--
-- DATE: February 28, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales
--
-- PROGRAMMER: Manuel Gonzales
--
-- INTERFACE: int main (void)
--
-- RETURNS: 0 in Success
--          1 in Failure
--
-- NOTES:
-- This function will Start the Message Queue, and will create the Send object to start sending the data.
----------------------------------------------------------------------------------------------------------------------*/
int main (int argc, char **argv)
{
	key_t mkey;
	int msq_id;
	long mtype;
	int port;

	struct msqid_ds msq_status;
	struct Message *msg = (struct Message*) malloc(sizeof(struct Message));

	
	switch(argc)
	{
		case 1:
			port = DEFAULT_PORT;
			mkey = MKEY;
			mtype = DEFAULT_TYPE;
		break;
		
		case 2:
			port = atoi(argv[1]);
			mkey = MKEY;
			mtype = DEFAULT_TYPE;
		break;
	
		case 3:
			port = atoi(argv[1]);
			mkey =	(key_t) atoi(argv[2]);
			mtype = DEFAULT_TYPE;
		break;

		case 4:
			port = atoi(argv[1]);
			mkey = (key_t) atoi(argv[2]);
			mtype = atol(argv[3]);
		break;

		default:
			fprintf(stderr, "Usage: %s Port Mkey Mtype\n", argv[0]);
			exit(1);
	}

	
    	/*---- Get Queue id ------*/
	if ((msq_id = msgget (mkey, IPC_CREAT)) < 0)
	{
		perror ("msgget failed!");
		exit(1);
	}

	/*--- get status info -----------------*/
	if (msgctl (msq_id, IPC_STAT, &msq_status) < 0)
	{
		perror ("msgctl (get status)failed!");
		exit(1);
	}

	/*-- print out status information -------*/
	mqstat_print (mkey, msq_id, &msq_status);
	
	Send sender(msq_id, mtype, msg, port);	

	while(1)
	{
		while(1)
		{
			
			signal(SIGINT, terminateP);
			
			if (sender.ReadQueue() == -1)
			{
				perror ("Error reading from the queue!");
				break;
			}
			if (sender.Verify() == -1)
			{
				perror ("Data received does not match");
				break;
			}
			if (sender.SendData() == -1)
			{
				perror ("Error sending data through Socket");
				break;
			}
		}
	}

	exit(0);
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: Send
--
-- DATE: February 28, 2015
-- 
-- REVISIONS: (Date and Description)
-- 
-- DESIGNER: Manuel Gonzales
-- 
-- PROGRAMMER: Manuel Gonzales
-- 
-- INTERFACE: Send::Send(int qid_s, long type_s, struct Message *message_s, int port_s)
-- 
-- qid_s : queue id
-- type_s : message type
-- message_s : message structure
-- port_s : port nuber /not sure if needed later on/
--
-- RETURNS: nothing
-- 
-- NOTES: Initalizes the values for the Sender Object.
-----------------------------------------------------------------------------------------------*/
Send::Send(int qid_s, long type_s, struct Message *message_s, int port_s)
{

	qid = qid_s;
	type = type_s;
	message = message_s;
	port = port_s;

	socket = -1;
	data_size = 0;

}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: ReadQueue
-- 
-- DATE: February 28, 2015
-- 
-- REVISIONS: (Date and Description)
-- 
-- DESIGNER: Manuel Gonzales
-- 
-- PROGRAMMER: Manuel Gonzales
-- 
-- INTERFACE: int Send::ReadQueue()
-- 
-- RETURNS: 0 on success, -1 on error
-- 
-- NOTES: Will read the 3 peices of information form the message queue 1 by 1 
-----------------------------------------------------------------------------------------------*/
int Send::ReadQueue()
{

	int error = 0;

	if((read_message(qid, type ,message)) == -1)
	{
		perror("error reading socket");
		error++;
	}

	sscanf(message->mesg_data, "%d", &socket);

	if((read_message(qid, type ,message)) == -1)
	{
		perror("error reading data size");
		error++;
	}

	data_size = atoi(message->mesg_data);

	if((read_message(qid, type ,message)) == -1)
	{
		perror("error reading data");
		error++;
	}

	memcpy (data, message->mesg_data, strlen(message->mesg_data)+1 );

	if(error > 0)
	{
		return -1;
	}

	return 0;
	
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: Verify
-- 
-- DATE: February 28, 2015
-- 
-- REVISIONS: (Date and Description)
-- 
-- DESIGNER: Manuel Gonzales
-- 
-- PROGRAMMER: Manuel Gonzales
-- 
-- INTERFACE: int Send::Verify()
-- 
-- RETURNS: 0 on success, -1 on error
-- 
-- NOTES: Will verify that the information received from the queue is right.
-----------------------------------------------------------------------------------------------*/
int Send::Verify()
{

	if(socket < 0)
	{
		perror("Invalid Socket");
		return -1;
	}

	if(data_size < 0)
	{
		perror("Invalid Data Size");
		return -1;
	}

	if(strlen(data) != data_size)
	{
		perror("Data does not match size");
		return -1;
	}

	return 0;

}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: SendData
-- 
-- DATE: February 28, 2015
-- 
-- REVISIONS: (Date and Description)
-- 
-- DESIGNER: Manuel Gonzales
-- 
-- PROGRAMMER: Manuel Gonzales
-- 
-- INTERFACE: int Send::SendData()
-- 
-- RETURNS: 0 on success, -1 on error
-- 
-- NOTES: Will send the data trough the selected socket
-----------------------------------------------------------------------------------------------*/
int Send::SendData()
{
	if(send (socket, data, BUFLEN, 0) == -1)
	{
		perror("Error Sending data through Socket\n");
		return -1;
	}	

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: terminateP
--
-- DATE: February 11, 2015
--
-- REVISIONS: February 28, 2015 Minor changes
--
-- DESIGNER: Manuel Gonzales
--
-- PROGRAMMER: Manuel Gonzales
--
-- INTERFACE: void terminateP(int sign)
--
-- RETURNS: nothing
--
-- NOTES:
-- This function will run once the server receives the SIGTERM signal and will make sure to close the
-- Message Queue (if default).
----------------------------------------------------------------------------------------------------------------------*/
void terminateP(int sign)
{ 	
	int mqid;

	if ((mqid = msgget (MKEY, IPC_CREAT)) < 0)
	{
		perror ("msgget failed!");
		exit(1);
	}
	
	/*-- Remove the message queue--*/
	if (msgctl (mqid, IPC_RMID, 0) < 0)
	{
		perror ("msgctl (remove queue) failed!");
		exit (1);
	}

	printf("CleanUp Complete (Default)\n");
	exit(0);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: read_message
--
-- DATE: February 11, 2015
--
-- REVISIONS: February 28, 2015 Fixed ctime.
--
-- DESIGNER: Aman Abdulla (class example) && Manuel Gonzales
--
-- PROGRAMMER: Aman Abdulla (class example) && Manuel Gonzales
--
-- INTERFACE: int read_message( int qid, long type, struct Message *message)
--
-- qid : queue id
-- type : message type
-- message : message structure
--
-- RETURNS: nothing
--
-- NOTES:
-- This function will Receive a message from the message type passed as an argument into the
-- message object.
----------------------------------------------------------------------------------------------------------------------*/
void mqstat_print (key_t mkey, int mqid, struct msqid_ds *mstat)
{

	printf ("\nKey %d, msg_qid %d\n\n", mkey, mqid);
	printf ("%d messages on queue\n\n", (int)mstat->msg_qnum);
	printf ("Last send by proc %d at %s\n",
           mstat->msg_lspid, ctime(&(mstat->msg_stime)));
	printf ("Last recv by proc %d at %s\n",
           mstat->msg_lrpid, ctime(&(mstat->msg_rtime)));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: read_message
--
-- DATE: February 11, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Aman Abdulla (class example) && Manuel Gonzales
--
-- PROGRAMMER: Manuel Gonzales
--
-- INTERFACE: int read_message( int qid, long type, struct Message *message)
--
-- qid : queue id
-- type : message type
-- message : message structure
--
-- RETURNS: 1 in Success
--          -1 in Failure
--
-- NOTES:
-- This function will Receive a message from the message type passed as an argument into the
-- message object.
----------------------------------------------------------------------------------------------------------------------*/
int read_message( int qid, long type, struct Message *message)
{
        int result;

        if((result = msgrcv( qid, message, sizeof(struct Message), type,  0)) == -1)
        {
                return(-1);
        }
        
        return(result);
}
