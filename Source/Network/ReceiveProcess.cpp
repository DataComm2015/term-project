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
--  void addSocket(Session *session);
--  void removeSocket(Session *session);
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
ReceiveProcess::ReceiveProcess(void* params, void (*handleSocket)(void* params, int socket))
{
    #ifdef DEBUG
    printf("receive: ReceiveProcess\n");
    #endif

    // initialize instance data
    this->params       = params;
    this->handleSocket = handleSocket;

    // open pipe
    if (pipe(ctrlPipe) < 0)
    {
        perror("failed to open pipe");
    }

    // create receive process
    pthread_create(&receiveThread,0,receiveRoutine,this);
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
    #ifdef DEBUG
    printf("receive: ~ReceiveProcess\n");
    #endif

    // close pipe, which implicitly tells receive process to shutdown
    close(ctrlPipe[1]);
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
-- INTERFACE:       void addSocket(Session *session)
--  new_sd:         pointer to session to add
--
-- RETURNS:         void
--
-----------------------------------------------------------------------------------------------*/
void ReceiveProcess::addSocket(int socket)
{
    #ifdef DEBUG
    printf("receive: addSocket %d\n",socket);
    #endif

    // create message to send on pipe
    ReceiveMessage msg;
    msg.type      = ADD_SOCKET;
    msg.socket_id = socket;

    // tell receive process of the new socket
    write(ctrlPipe[1],&msg,sizeof(msg));
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        removeSocket
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Alex Lam
--
-- PROGRAMMER:      Alex Lam, Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       void removeSocket(Session *session)
--  session:        pointer to the session to remove
--
-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void ReceiveProcess::removeSocket(int socket)
{
    #ifdef DEBUG
    printf("receive: removeSocket %d\n",socket);
    #endif

    // create message to send on pipe
    ReceiveMessage msg;
    msg.type      = REMOVE_SOCKET;
    msg.socket_id = socket;

    // tell receive process to remove the socket
    write(ctrlPipe[1],&msg,sizeof(msg));
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
    #ifdef DEBUG
    printf("receive process started...\n");
    #endif

    // parse thread parameters
    ReceiveProcess* dis = (ReceiveProcess*) params;

    // set up files structure
    Files files;
    files_init(&files);
    files_add_file(&files,dis->ctrlPipe[0]);

    while(true)
    {
        // wait for activity to occur
        files_select(&files);

        // handle control pipe activity
        if(FD_ISSET(dis->ctrlPipe[0],&files.selectFds))
        {
            ReceiveMessage msg;
            #ifdef DEBUG
            printf("handle control pipe activity\n");
            #endif

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
                #ifdef DEBUG
                printf("adding socket %d\n",msg.socket_id);
                #endif
                break;

            // remove a socket from socket set
            case REMOVE_SOCKET:
                // remove the socket from set of files to select
                files_rm_file(&files,msg.socket_id);
                #ifdef DEBUG
                printf("rming socket %d\n",msg.socket_id);
                #endif
                break;
            }
        }

        // handle socket activity
        for(auto socket = files.fdSet.end(); socket != files.fdSet.begin();
            --socket)
        {
            int selectedSocket = *socket;

            if(FD_ISSET(selectedSocket,&files.selectFds)
                && selectedSocket != dis->ctrlPipe[0])
            {
                dis->handleSocket(dis->params,selectedSocket);
            }
        }
    }


    #ifdef DEBUG// cleanup
    printf("receive process stopped...\n");
    #endif

    return 0;
}
