/*-----------------------------------------------------------------------------
-- SOURCE FILE: Session.h - The header file for Networking Sessions.
--
-- CLASS: Session
--
-- DATE: February, 17, 2015
--
-- REVISIONS: -
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-- A Session is used to read and write messages to a connected socket through
-- a supplied ReadProcess and SendProcess. Messages received are handled
-- locally if they relate to the connection itself, or through the
-- supplied NetworkEntityMultiplexer if the message relates to
-- NetworkEntities.
-----------------------------------------------------------------------------*/

#ifndef _NETWORK_SESSION_H_
#define _NETWORK_SESSION_H_

#include <deque>
#include <set>
#include <cstring>
#include "semaphores.h"


namespace Networking
{
    class Session;
    void handleSessionMessages();

    static int SESSION_SET_SEM_KEY = 226;
    static int SESSION_SEM = createSem(SESSION_SET_SEM_KEY);
    static int MESSAGE_SEM_KEY = 9956;
    static std::set<Session*> SESSIONS;

    class NetworkEntity;
    class NetworkEntityMultiplexer;
    struct Message;

    class Session
    {
    friend class NetworkEntity;
    friend class NetworkEntityMultiplexer;

    public:
        Session(int socket);
        virtual ~Session();
        void send(Message* msg);
        void disconnect();
        void onMessage(Message* msg);
        void onDisconnect(int remote);
        void handleMessages();


    private:
        int socket;
        int messagesSem;
        NetworkEntityMultiplexer* entityMux;
        std::set<NetworkEntity*> registeredEntities;
        std::deque<Message*> messages;

    };
}

#endif
