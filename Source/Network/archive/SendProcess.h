#ifndef _SEND_PROCESS_H_
#define _SEND_PROCESS_H_

#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>

#define NETWORK_MESSAGE_SIZE 512

namespace Networking
{
    struct Message;
    class Session;

    enum SendMessageType
    {
        ADD_SOCKET = 0,
        REMOVE_SOCKET = 1,
        SEND_MESSAGE = 2,
        SHUTDOWN = 3
    };

    struct SendMessage
    {
        SendMessageType type;
        int socket;
        char data[NETWORK_MESSAGE_SIZE];
    };


    class SendProcess
    {
        public:
            SendProcess();
            ~SendProcess();
            void sendToChild(Session *session, Message *message_s);
            void addSession(Session *session);
            void removeSession(Session *session);

        private:
            void awaitFurtherInstructions();
            void closeSockets(bool parent);
            int sendPartial(SendMessage* m, int length);
            void sendNetworkMessage(int socket, char* message);

            int pid;
            int qid;
            /*
                sockets keeps a map of the parent int value for the socket as key
                and the child int value for the socket as value.
             */
            std::map<int, int> sockets;
    };


}

#endif
