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
#include <cstdlib>


namespace Networking
{
    class Session;
    class NetworkEntity;
    class NetworkEntityMultiplexer;
    struct Message;

    void handleSessionMessages();

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
        void markForDeletion();

    private:
        int socket;
        int messagesSem;
        std::deque<Message*> messages;
        NetworkEntityMultiplexer* entityMux;
        std::set<NetworkEntity*> registeredEntities;

    };
}

#endif
