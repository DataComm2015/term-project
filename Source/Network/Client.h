#ifndef CLIENT_H_
#define CLIENT_H_

#include "Session.h"

#include <pthread.h>
#include <map>

namespace Networking
{
    class Client
    {
    public:
        Client();
        virtual ~Client();
        int connect(char* remoteName, short remotePort);
    private:
        virtual void onConnect(int socket);
        virtual void onMessage(int socket, char* data, int len);
        virtual void onDisconnect(int socket, int remote);
        static void* clientRoutine(void* params);

        /**
         * pipe used to communicate with the clientThread.
         */
        int ctrlPipe[2];

        /**
         * thread id for the thread that runs the clientRoutine.
         */
        pthread_t clientThread;

        /**
         * maps sockets to sessions.
         */
        std::map<int,Session*> sessions;
    };
}

#endif
