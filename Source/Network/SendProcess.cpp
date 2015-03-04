#include "SendProcess.h"

#include "Message.h"
#include "Session.h"

#include <stdlib.h>

Networking::SendProcess::SendProcess()
{
	// < -- Create Message Queue here -- >
	
	// Fork Process
	pid = fork();
	
	// Child Process waits for instructions
	if (pid == 0)
	{
		awaitFurtherIntructions();
	}
}

Networking::SendProcess::~SendProcess()
{
	if (pid == 0)
	{
		// < -- CLOSE ALL SOCKETS HERE -- >
		
		// Exit the Child Process
		exit(0);
	}
	else if (pid > 0)
	{
		// < -- SEND KILL MESSAGE TO CHILD HERE -- >
	
		// Wait for Child to Die
		int status = 0;
		wait(pid, &status, 0);
		
		// < -- CLOSE ALL SOCKETS HERE -- >
	}
}

void Networking::SendProcess::send(Session *session, Message *message_s)
{
	// Create Message to send to child process.
	SendMessage message;
	message.type = SEND_MESSAGE;
	message.socket = session->getSocket();
	memcpy(message.data, message_s, NETWORK_MESSAGE_LENGTH);

	// < -- WRITE MESSAGE TO MESSAGE QUEUE HERE -- >
}

void addSession(Session *session)
{
	int socket = session->getSocket();
	// < -- TRANSFER SOCKET TO PROCESS HERE -- >
	// < -- WRITE "ADD SOCKET" MESSAGE TO MESSAGE QUEUE HERE -- >
}

void removeSession(Session *session)
{
	int socket = session->getSocket();
	// < -- WRITE "REMOVE SOCKET" MESSAGE TO MESSAGE QUEUE HERE -- >
}

void awaitFurtherInstructions()
{
	while (1)
	{
		// < -- READ FROM MESSAGE QUEUE HERE -- >
	
		// < -- IF MESSAGE WAS ADD SOCKET, ADD SOCKET HERE -- >
		// < -- IF MESSAGE WAS REMOVE SOCKET, REMOVE SOCKET HERE -- >
		// < -- IF MESSAGE WAS SEND MESSAGE: -- >
			// < -- WHILE MESSAGE DATA NOT FULLY SENT, SEND MESSAGE DATA TO ID'D SOCKET -- >
	}
}
