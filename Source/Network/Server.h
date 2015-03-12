#ifndef SERVER_H_
#define SERVER_H_

#include <map>

namespace Networking
{
    class ReceiveProcess;

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
        static void* listeningRoutine(void* params);
        static void onSocketActivity(void* dis, int socket);
        ReceiveProcess* receiveProcess;
        int svrSock;
        // std::map<int,Session*> sessions;
    };
}

#endif
