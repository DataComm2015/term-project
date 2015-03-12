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
--  ~ReceiveProcess();
--  void addSession(Session *session);
--  void removeSession(Session *session);
--  void onMessageReceived(int socket, Message *message);
--  void runProcess();
--  void closeProcess();
--
--
-- NOTES: This file provides definitions for a ReceiveProcess object.
-----------------------------------------------------------------------------------------------*/
#include "ReceiveProcess.h"
// #include "Message.h"
// #include "ancillary.h"
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
#include <sys/time.h>
#include <iostream>
#include <signal.h>
#include <vector>
#include <signal.h>

using namespace Networking;

// set initial value of static variable
ReceiveProcess* ReceiveProcess::instance = 0;

ReceiveProcess* ReceiveProcess::getInstance()
{
    if(instance == 0)
    {
        instance = new ReceiveProcess();
    }

    printf("receive: getInstance %p\n",instance);
    return instance;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        sig_handler
--
-- DATE:            February 21, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Eric Tsang
--
-- INTERFACE:       void sig_handler()
--
-- RETURNS:         void
--
-- NOTES:           calls onMessageReceived after the receive process signals the main process

                            this will need the process -> game pipe
                            //int p2[2];

-----------------------------------------------------------------------------------------------*/

/*void ReceiveProcess::sig_handler(int signum)
{
    printf("receive: sig_handler\n");
    // allocate data to hold data from pipe
    int socket;
    int messagelength;
    void* msgData;
    Message message;

    // read header data from pipe
    read(p2[0], &socket, sizeof(int));
    read(p2[0], &messagelength, sizeof(int));
    read(p2[0], &message.type, sizeof(int));
    read(p2[0], &message.len, sizeof(int));

    // allocate space for payload
    msgData = malloc(message.len);
    message.data = msgData;

    // read in payload
    read(p2[0], msgData, message.len);

    // invoke callback
    onMessageReceived(socket, message);
}*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        ReceiveProcess
--
-- DATE:            February 21, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam
--
-- INTERFACE:       Receive::ReceiveProcess()
--
-- RETURNS:         void
--
-- NOTES:           Initalizes the ReceiveProcess object,
                    creating the socket for file descriptors to be shared between processes,
                    creates child process
-----------------------------------------------------------------------------------------------*/
/*ReceiveProcess::ReceiveProcess()
{
    printf("receive: ReceiveProcess\n");
    static onetimeSetupComplete = false;

    if(!onetimeSetupComplete)
    {
        onetimeSetupComplete = true;

        signal(SIGUSR1, sig_handler);

        // open pipe used to talk with main process
        if (pipe(p2) < 0)
        {
            perror("pipe call");
        }
    }

    // open pipe used to talk with receive process
    if (pipe(p) < 0)
    {
        perror("pipe call");
    }

    // create pipe used to share sockets with other processes
    if(socketpair(PF_UNIX, SOCK_STREAM, 0, ipcsock))
    {
        perror("socketpair");
    }

    // create receive process
    pid = fork();
    switch(pid)
    {
    case -1:
        perror("Fork Failed!");
        break;
    case  0:
        close(ipcsock[0]);
        runProcess();
        break;
    default:
        close(ipcsock[1]);
        break;
    }
}*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        addSocket
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam
--
-- INTERFACE:       void addSession(Session *session)
--  new_sd:         pointer to session to add
--
-- RETURNS:         void
--
-----------------------------------------------------------------------------------------------*/
/*void ReceiveProcess::addSession(Session *session)
{
    printf("receive: addSession\n");
    unsigned int new_sd = session->getSocket();

    // Add Socket to Map on Parent Process
    sessions.insert(std::pair<int, Session*>(new_sd, session));

    // Transfer Socket
    ancil_send_fd(ipcsock[0], new_sd);

    // Create Message to Send on Pipe
    ReceiveMessage message;
    message.type = ADD_SOCKET;
    message.socket_id = new_sd;

    // Inform child process of new Socket
    write(p[1], &message, 1);
}*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        removeSession
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Jeff Bayntun
--
-- INTERFACE:       void removeSession(Session *session)
--  session:        pointer to the session to remove
--
-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
/*void ReceiveProcess::removeSession(Session *session)
{
    printf("receive: removeSession\n");
    unsigned int sd = session->getSocket();

    // Remove Socket from Map on Parent Process
    sessions.erase(sd);
    close(sd);

    // Create Message to Send on Pipe
    ReceiveMessage message;
    message.type = REMOVE_SOCKET;
    message.socket_id = sd;

    // Inform child process of new Socket
    write(p[1], &message, 1);
}*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        onmessageReceived
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam
--
-- INTERFACE:       void onMessageReceived(int socket, Message *message)
--
-- RETURNS:         void
--
-- NOTES:           Calls the "onMessageReceived" method of the Session that received data.
-----------------------------------------------------------------------------------------------*/
/*void ReceiveProcess::onMessageReceived(int socket, Message *message)
{
    printf("receive: onMessageReceived\n");
    Session *session = sessions[socket];
    session->onMessageReceived(message);
}*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        closeProcess
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam
--
-- INTERFACE:       void Receive::closeProcess()
--
-- RETURNS:         void
--
-- NOTES:           Writes close signal to the receive process
-----------------------------------------------------------------------------------------------*/
/*void ReceiveProcess::closeProcess()
{
    printf("receive: closeProcess\n");
    ReceiveMessage message;
    message.type = SHUTDOWN;
    message.socket_id = 0;

    write(p[1], &message, sizeof(ReceiveMessage));
}*/

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        runProcess
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Jeff Bayntun
--
-- INTERFACE:       void Receive::runProcess()
--
-- RETURNS:         void
--
-- NOTES:           The main point of this program,
                    This process starts by initalizing it's set of file descriptors to monitor for select
                    Then it monitors the pipe between this process and the main for any messages
                    and checks for any tcp data coming in.
-----------------------------------------------------------------------------------------------*/
/*void ReceiveProcess::runProcess()
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
            FD_SET(it->second, &readfds);
            if(it->second > max_sd)
            {
                max_sd = it->second;
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
                close(it->second);
            }

            // Print the error
            cerr << "receive process error: " << errno << endl;
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
}*/
