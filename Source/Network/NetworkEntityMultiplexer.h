#ifndef NETWORKENTITYMULTIPLEXER_H
#define NETWORKENTITYMULTIPLEXER_H

#include <map>
#include <set>

#define MSG_TYPE_WARNING    -1
#define MSG_TYPE_UPDATE     0
#define MSG_TYPE_REGISTER   1
#define MSG_TYPE_UNREGISTER 2

namespace Networking
{
    class Message;
    class Session;
    class NetworkEntity;

    class NetworkEntityMultiplexer
    {
    friend class NetworkEntity;
    public:
        static NetworkEntityMultiplexer* getInstance();
        static void setInstance(NetworkEntityMultiplexer* mux);
        void onMessage(Session* session, Message msg);
    protected:
        NetworkEntityMultiplexer();
        virtual ~NetworkEntityMultiplexer();
        virtual NetworkEntity* onRegister(int id, int entityType, Session* session, Message msg);
    private:
        void update(int id, std::set<Session*>& sessions, Message msg);
        void registerSession(int id, int type, Session* session, Message msg);
        void unregisterSession(int id, Session* session, Message msg);
        void onUpdate(int id, Message msg);
        void onUnregister(int id, Session* session, Message msg);
        static NetworkEntityMultiplexer* instance;
        std::map<int,NetworkEntity*> entities;
    };
}

#endif
