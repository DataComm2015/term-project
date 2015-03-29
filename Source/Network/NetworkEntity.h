#ifndef NETWORK_ENTITY_H
#define NETWORK_ENTITY_H

#include <set>

/**
 * network entity subclass type identifiers.
 */
#define CLIENT_INPUT_CLASS 0
#define NET_CONTROLER_CLASS 1

namespace Networking
{
    class NetworkEntityMultiplexer;
    class Session;
    class Message;

    class NetworkEntity
    {
    friend class Session;
    friend class NetworkEntityMultiplexer;
    public:
        NetworkEntity(int id, int type);
        NetworkEntity(int type);
        ~NetworkEntity();
        void update(Message message);
        void registerSession(Session * session, Message message);
        void unregisterSession(Session * session, Message message);
        
        int type;
        int id;
    protected:
        virtual void onRegister(Session *session);
        virtual void onUnregister(Session * session, Message message);
        virtual void onUpdate(Message message);
    private:
        void silentRegister(Session* session);
        void silentUnregister(Session* session);
        static int nextId;
        NetworkEntityMultiplexer* mux;
        std::set< Session * > registeredSessions;

    };
}

#endif
