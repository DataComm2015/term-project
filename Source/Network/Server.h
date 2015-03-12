#ifndef SERVER_H_
#define SERVER_H_

#include <vector>

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
        virtual void onConnect(Session* session);

    private:
        static void* listeningThread(void* params);
        int svrSock;
        std::vector<Session*> sessions;
    };
}

#endif
