#ifndef SERVER_H_
#define SERVER_H_

#include <set>

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
        std::set<Session*> sessions;
    };
}

#endif
