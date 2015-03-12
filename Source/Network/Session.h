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

namespace Networking
{
    class Socket;
    // class ReceiveProcess;
    // class SendProcess;
    // class NetworkEntityMultiplexer;

    struct Message;

    class Session
    {
    friend class ReceiveProcess;

    public:
        Session(int socket);
        virtual ~Session();
        void send(Message *message);
        void disconnect();

    private:
        void onMessageReceived(Message *message);
        void onConnectionClosedByRemote();

        int socket;
        // ReceiveProcess* recvProcess;
        // SendProcess* sendProcess;
        // NetworkEntityMultiplexer* entityMux;
    };
}

#endif
