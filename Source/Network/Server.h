#ifndef SERVER_H_
#define SERVER_H_

#include <map>
#include <pthread.h>

namespace Networking
{
    class Session;

    class Server
    {
    public:
        Server();
        virtual ~Server();
        int startServer(short port);
        int stopServer();
    protected:
        Session* getSession(int socket);
        virtual void onConnect(int socket);
        virtual void onMessage(int socket, char* data, int len);
        virtual void onDisconnect(int socket, int remote);
    private:
        static void* serverRoutine(void* params);

        /**
         * server socket used to listen for new connections to the server.
         */
        int svrSock;

        /**
         * pipe used to communicate with the serverThread.
         */
        int ctrlPipe[2];

        /**
         * thread id for the thread that runs the serverRoutine.
         */
        pthread_t serverThread;

        /**
         * maps sockets to sessions.
         */
        std::map<int,Session*> sessions;
    };
}

#endif
