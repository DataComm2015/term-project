/*----------------------------------------------------------------------------------------------
-- DATE: February 21, 2015
--
-- Source File: ReceiveProcess.cpp
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER: Alex Lam, Calvin Rempel, Jeff Bayntun, Manuel Gonzales, Eric Tsang
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
#include "Message.h"
#include "Session.h"
#include "select_helper.h"

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
-- FUNCTION:        ReceiveProcess
--
-- DATE:            February 21, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Eric Tsang
--
-- INTERFACE:       Receive::ReceiveProcess()
--
-- RETURNS:         void
--
-- NOTES:           Initalizes the ReceiveProcess object,
                    creating the socket for file descriptors to be shared between processes,
                    creates child process
-----------------------------------------------------------------------------------------------*/
ReceiveProcess::ReceiveProcess()
{
    printf("receive: ReceiveProcess\n");

    // open pipe
    if (pipe(ctrlPipe) < 0)
    {
        perror("failed to open pipe");
    }

    // create receive process
    pthread_t thread;
    pthread_create(&thread,0,receiveRoutine,this);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        addSocket
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Eric Tsang
--
-- INTERFACE:       void addSession(Session *session)
--  new_sd:         pointer to session to add
--
-- RETURNS:         void
--
-----------------------------------------------------------------------------------------------*/
void ReceiveProcess::addSession(Session* session)
{
    printf("receive: addSession %p\n",session);

    // add socket to map on parent process
    sessions[session->socket] = session;

    // create message to send on pipe
    ReceiveMessage msg;
    msg.type      = ADD_SOCKET;
    msg.socket_id = session->socket;

    // tell receive process of the new socket
    write(ctrlPipe[1],&msg,sizeof(msg));
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        removeSession
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       void removeSession(Session *session)
--  session:        pointer to the session to remove
--
-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void ReceiveProcess::removeSession(Session* session)
{
    printf("receive: removeSession %p\n",session);

    // remove socket from map on parent process
    sessions.erase(session->socket);

    // create message to send on pipe
    ReceiveMessage msg;
    msg.type      = REMOVE_SOCKET;
    msg.socket_id = session->socket;

    // tell receive process to remove the socket
    write(ctrlPipe[1],&msg,sizeof(msg));
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        closeProcess
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Eric Tsang
--
-- INTERFACE:       void Receive::closeProcess()
--
-- RETURNS:         void
--
-- NOTES:           Writes close signal to the receive process
-----------------------------------------------------------------------------------------------*/
ReceiveProcess::~ReceiveProcess()
{
    printf("receive: ~ReceiveProcess\n");

    // close pipe, which implicitly tells receive process to shutdown
    close(ctrlPipe[1]);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        runProcess
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Jeff Bayntun, Eric Tsang
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
void* ReceiveProcess::receiveRoutine(void* params)
{
    printf("receive process started...\n");

    // parse thread parameters
    ReceiveProcess* dis = (ReceiveProcess*) params;

    // set up files structure
    Files files;
    files_init(&files);
    files_add_file(&files,dis->ctrlPipe[0]);

    while(true)
    {
        // wait for activity to occur
        int activity = files_select(&files);

        // an error has occured
        if(activity == -1)
        {
            break;
        }

        // handle control pipe activity
        if(FD_ISSET(dis->ctrlPipe[0],&files.selectFds))
        {
            ReceiveMessage msg;
            printf("handle control pipe activity\n");

            // read from pipe
            int result = read(dis->ctrlPipe[0],&msg,sizeof(msg));

            // terminate the receive process when the control pipe is closed, or
            // encounters an error.
            if(result == 0 || result == -1)
            {
                break;
            }

            // deal with the read data otherwise
            switch(msg.type)
            {

            // add a socket to socket set
            case ADD_SOCKET:
                // add socket to set of files to select
                files_add_file(&files,msg.socket_id);
                printf("adding socket %d\n",msg.socket_id);
                break;

            // remove a socket from socket set
            case REMOVE_SOCKET:
                // remove the socket from set of files to select
                files_rm_file(&files,msg.socket_id);
                printf("rming socket %d\n",msg.socket_id);
                break;
            }
        }

        // handle socket activity
        for(auto socket = files.fdSet.begin(); socket != files.fdSet.end();
            ++socket)
        {
            int selectedSocket = *socket;

            if(FD_ISSET(selectedSocket,&files.selectFds)
                && selectedSocket != dis->ctrlPipe[0])
            {
                // printf("handle socket activity\n");

                Message msg;

                // read from socket
                int result = read(selectedSocket,&msg.type,sizeof(msg.type));

                // remove socket if the socket encounters an error, or is closed
                if(result == 0 || result == -1)
                {
                    printf("close socket %d\n",selectedSocket);
                    // close the socket
                    close(selectedSocket);
                    // remove the socket from set of files to select
                    files_rm_file(&files,selectedSocket);
                    // invoke session callback
                    dis->sessions[selectedSocket]->onConnectionClosedByRemote();
                }
                else
                {
                    // deal with the read data otherwise by writing the received
                    // data to the main process through a pipe
                    read(selectedSocket,&msg.len,sizeof(msg.len));
                    void* buffer = malloc(msg.len);
                    read(selectedSocket,buffer,msg.len);

                    // invoke session callback
                    msg.data = buffer;
                    dis->sessions[selectedSocket]->onMessageReceived(&msg);

                    // cleanup...
                    free(buffer);
                }
            }
        }
    }

    // cleanup
    printf("receive process stopped...\n");

    return 0;
}
