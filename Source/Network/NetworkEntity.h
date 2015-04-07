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
        virtual ~NetworkEntity();
        virtual void update(Message message);
        void registerSession(Session * session, Message message);
        void unregisterSession(Session * session, Message message);
        int getType();
	    int getId();
    protected:
        virtual void onRegister(Session *session);
        virtual void onUnregister(Session * session, Message message);
        virtual void onUpdate(Message message);
        NetworkEntityMultiplexer* mux;
        const int type;
        const int id;
    private:
        int silentRegister(Session* session);
        int silentUnregister(Session* session);
        static int nextId;
        std::set< Session * > registeredSessions;
    };
}

#endif
