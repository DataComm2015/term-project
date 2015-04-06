#include "SendProcess.h"

#include "Session.h"
#include "Message.h"


/*----------------------------------------------------------------------------------------------
-- FUNCTION:        SendProcess
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel, Jeff Bayntun, Manuel Gonzales
--
-- INTERFACE:       SendProcess()
--
--
-- NOTES:           Creates a SendProcess Object, opens a message queue
                    and forks a child process to handle network calls
-----------------------------------------------------------------------------------------------*/
Networking::SendProcess::SendProcess()
{
    // < -- Create Message Queue here -- >
    key_t mkey = ftok(".", 'a');
    if ((qid = msgget (mkey, IPC_CREAT)) < 0)
    {
        perror ("msgget failed!");
        exit(1);
    }
    // Fork Process
    pid = fork();

    // Child Process waits for instructions
    if (pid == 0)
    {
        awaitFurtherInstructions();
    }
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        ~SendProcess
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel, Jeff Bayntun, Manuel Gonzales
--
-- INTERFACE:       ~SendProcess()
--
--
-- NOTES:           Destructor for SendProcess. Closes sockets and
                    kills child Process
-----------------------------------------------------------------------------------------------*/
Networking::SendProcess::~SendProcess()
{
    if (pid == 0)
    {
        closeSockets(false);

        // Exit the Child Process
        exit(0);
    }
    else if (pid > 0)
    {
        kill(pid, SIGKILL);
        // Wait for Child to Die
        int status = 0;
        waitpid(pid, &status, 0);
        closeSockets(true);
    }
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        send
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel, Jeff Bayntun, Manuel Gonzales
--
-- INTERFACE:       void send(Session *session, Message *message_s)
-- session:         pointer to session message will be sent to
-- message_s:       pointer to message struct to send
--
--
-- NOTES:           Sends messages to child process via queue so they can
                    be sent across the network
-----------------------------------------------------------------------------------------------*/
void Networking::SendProcess::sendToChild(Session *session, Message *message_s)
{
    int sent = 0;
    int to_copy, result;

    // Create Message to send to child process.
    SendMessage message;
    int length = sizeof(SendMessage);
    message.type = SEND_MESSAGE;
    message.socket = session->getSocket();

    // send message to child
    while(sent < message_s->len)
    {
        memset(message.data, 0, NETWORK_MESSAGE_SIZE);
        to_copy = ((message_s->len - sent) > NETWORK_MESSAGE_SIZE) ? NETWORK_MESSAGE_SIZE: (message_s->len - sent);
        memcpy(message.data, message_s+sent, to_copy);
        if((result = sendPartial(&message, length)) == -1)
        {
            break;
        }
        sent += result;
    }
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        addSession
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel, Jeff Bayntun
--
-- INTERFACE:       void addSession(Session *session)
-- session:         pointer to session to add
--
--
-- NOTES:           sends message to child process to add this session
-----------------------------------------------------------------------------------------------*/
void Networking::SendProcess::addSession(Session *session)
{
    int socket = session->getSocket();
    // < -- TRANSFER SOCKET TO PROCESS HERE -- >

    // send message to queue for child to add socket
    SendMessage message;
    int length = sizeof(SendMessage);

    message.type = ADD_SOCKET;
    message.socket = socket;

    if(msgsnd(qid, &message, length, 0) == -1)
    {
        perror("error sending message");
    }
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        removeSession
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void removeSession(Session *session)
-- session:         pointer to session to remove
--
--
-- NOTES:           sends message to child process to remove this session
-----------------------------------------------------------------------------------------------*/
void Networking::SendProcess::removeSession(Session *session)
{
    int socket = session->getSocket();
    // send message to queue for child to remove socket
    SendMessage message;
    int length = sizeof(SendMessage);
    message.type = REMOVE_SOCKET;

    if(msgsnd(qid, &message, length, 0) == -1)
    {
        perror("error sending message");
    }
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        awaitFurtherInstructions
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel, Jeff Bayntun
--
-- INTERFACE:       void awaitFurtherInstructions()
--
--
-- NOTES:           child Process waits for instructions from message queue, then takes
                    action based on message type
-----------------------------------------------------------------------------------------------*/
void Networking::SendProcess::awaitFurtherInstructions()
{
    SendMessage message;
    size_t result;
    int length = sizeof(SendMessage);
    int parent_value;
    while (1)
    {
        // < -- READ FROM MESSAGE QUEUE HERE -- >

        memset(&message, 0, sizeof(SendMessage));


        if( (result = msgrcv(qid, &message, length, 0, 0)) == -1)
        {
            perror("error receiving message");
            break;
        }

        switch(message.type)
        {
            case ADD_SOCKET:
                // todo: get real socket in parent value
                parent_value = 99;
                //  parent_value  = ???
                sockets.insert({parent_value, message.socket});
                break;
            case REMOVE_SOCKET:
                sockets.erase(message.socket);
                break;
            case SEND_MESSAGE:
                //write message to network over properly mapped socket
                sendNetworkMessage(message.socket, message.data);
                break;
            case SHUTDOWN:
                closeSockets(false);
                return;
            default:
                break;
        }
    }
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        closeSockets
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void closeSockets(bool parent)
-- parent:          true if this is the parent process
--
--
-- NOTES:           closes all sockets in the sockets map
-----------------------------------------------------------------------------------------------*/
void Networking::SendProcess::closeSockets(bool parent)
{

    std::map<int,int>::iterator it;
    for (it = sockets.begin(); it != sockets.end(); ++it)
    {
        if(parent)
            close(it->first);
        else
            close(it->second);
    }
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        sendPartial
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       int sendPartial(bool parent)
-- message:         pointer to message to send
-- length:          length to send
--
-- RETURN:          the number of bytes sent, -1 on error
--
--
-- NOTES:           sends a full message to the queue, which may be a part of the actual
                    message.
-----------------------------------------------------------------------------------------------*/
int Networking::SendProcess::sendPartial(SendMessage* message, int length)
{
    int result;
    if((result = msgsnd(qid, message, length, 0)) == -1)
    {
        perror("error sending message");
    }
    return result;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        sendNetworkMessage
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       sendNetworkMessage(int socket, char* message)
-- socket:          socket to send message accross
-- message:         pointer to char array to send
--
-- RETURN:          void
--
--
-- NOTES:           sends a message across the network to the given socket.  Messages are
                    always of size defined by NETWORK_MESSAGE_SIZE
-----------------------------------------------------------------------------------------------*/
void Networking::SendProcess::sendNetworkMessage(int socket, char* message)
{
    int result;
    int sent = 0;
    while (sent < NETWORK_MESSAGE_SIZE)
    {
        if((result = send(socket, message, NETWORK_MESSAGE_SIZE, 0)) == -1)
        {
            perror("error sending across network");
            return;
        }
        sent += result;
    }
}

