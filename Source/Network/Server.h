#ifndef SERVER_H_
#define SERVER_H_

#include <map>

namespace Networking
{
    class Server
    {
    public:
        Server();
        virtual ~Server();
        int startServer(short port);
        int stopServer();
        virtual void onConnect(int socket);
        virtual void onMessage(int socket, char* data, int len);
        virtual void onDisconnect(int socket, int remote);

    private:
        static void* serverRoutine(void* params);
        int svrSock;
        pthread_t serverThread;
    };
}

#endif
