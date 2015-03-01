#ifndef NETWORKENTITYMULTIPLEXER_H
#define NETWORKENTITYMULTIPLEXER_H

#include <map>
#include <set>
#include <stdlib.h>
#include <string.h>

#include "Message.h"
#include "Session.h"
#include "NetworkEntity.h"

#define MSG_TYPE_UPDATE     0
#define MSG_TYPE_REGISTER   1
#define MSG_TYPE_UNREGISTER 2

namespace Networking
{
    class NetworkEntityMultiplexer
    {
    public:
    friend class NetworkEntity;
        /**
         * method with the same signature as the Session::onMessage. this
         *   function should be invoked within the session's onMessage method
         *   and forwarded the parameters if the message received by the session
         *   was sent from another {NetworkEntityMultiplexer}.
         *
         * @function   NetworkEntityMultiplexer::onMessage
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  int onMessage(Session* session, Message msg);
         *
         * @param      session session that received the message
         * @param      msg message received from a session object.
         *
         * @return integer indicating the outcome of the operation
         */
        int onMessage(Session* session, Message msg);
    protected:
        /**
         * should only be called from within the Networking library. it creates
         *   a new NetworkEntity subclass instance, and returns it to the
         *   {NetworkEntityMultiplexer}.
         *
         * this method should be overridden to instantiate an instance of a
         *   subclass of the {NetworkEntity}, and return it.
         *
         * @function   NetworkEntityMultiplexer::onRegister
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  virtual NetworkEntity* onRegister(int id, int entityType,
         *   Session* session, Message msg) = 0;
         *
         * @param  id identifier associated with a {NetworkEntity} instance.
         * @param  entityType type of the entity, hinting at what kind of
         *   {NetworkEntity} sub class object to instantiate.
         * @param  session session being registered with the NetworkEntity.
         * @param  msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         *
         * @return     pointer to the new {NetworkEntity} that was registered
         */
        virtual NetworkEntity*
        onRegister(int id, int entityType, Session* session, Message msg) = 0;
    private:
        /**
         * should only be called by {NetworkEntity} objects only. it
         *   encapsulates the passed data into a packet, to be sent to all
         *   session objects registered with the {NetworkEntity} associated with
         *   {id}.
         *
         * @function   NetworkEntityMultiplexer::update
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  int update(int id, std::set<Session*>& sessions, Message
         *   msg);
         *
         * @param      id identifier associated with a {NetworkEntity} instance
         * @param      sessions set of sessions associated with the network
         *   entity that need to be informed of the update
         * @param      msg describes the message to send over the wire
         *
         * @return     integer indicating the result of the operation
         */
        int update(int id, std::set<Session*>& sessions, Message msg);
        /**
         * should only be called by the {NetworkEntity} class. it registers the
         *   passed {Session} object with the {NetworkEntity} associated with
         *   {id}, and sends the {msg} to the {session}.
         *
         * @function   NetworkEntityMultiplexer::registerSession
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  int registerSession(int id, int type, Session* session,
         *   Message msg)
         *
         * @param      id identifier associated with a {NetworkEntity} instance
         * @param      type type of entity that's being registered
         * @param      session {Session} to be registered with the
         *   {NetworkEntity} instance
         * @param      msg describes the message to send over the wire. this
         *   message is only sent to the {session}.
         *
         * @return     integer indicating the result of the operation
         */
        int registerSession(int id, int type, Session* session, Message msg);
        /**
         * should only be invoked by the {NetworkEntity} class. it unregisters
         *   the {session} from the {NetworkEntity} instance associated with
         *   {id}, and sends the {msg} to the {session}.
         *
         * @function   NetworkEntityMultiplexer::unregisterSession
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  int unregisterSession(int id, Session* session, Message
         *   msg)
         *
         * @param      id identifier associated with a {NetworkEntity} instance
         * @param      session {Session} to be unregistered with the
         *   {NetworkEntity} instance
         * @param      msg describes the message to send over the wire. this
         *   message is only sent to the {session}.
         *
         * @return     integer indicating the result of the operation
         */
        int unregisterSession(int id, Session* session, Message msg);
        /**
         * should only be called from within the Networking library. it calls
         *   the update method of the {NetworkEntity} instance associated with
         *   {id}.
         *
         * @function   NetworkEntityMultiplexer::onUpdate
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  void onUpdate(int id, Message msg)
         *
         * @param      id identifier associated with a {NetworkEntity} instance.
         * @param      msg describes the message to send over the wire. this
         *   message is only sent to the {session}.
         */
        void onUpdate(int id, Message msg);
        /**
         * should only be called from within the Networking library. it calls
         *   the onUnregister method of the {NetworkEntity} instance associated
         *   with {id}.
         *
         * @function   NetworkEntityMultiplexer::onUnregister
         *
         * @date       2015-02-28
         *
         * @revision   none
         *
         * @designer   Networking Team
         *
         * @programmer Eric Tsang
         *
         * @note       none
         *
         * @signature  void onUnregister(int id, Session* session, Message msg)
         *
         * @param      id identifier associated with a {NetworkEntity} instance.
         * @param      session session being registered with the NetworkEntity.
         * @param      msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         */
        void onUnregister(int id, Session* session, Message msg);
        /**
         * contains references to network entities.
         *
         * the keys to the map are the IDs of the network entities, and the
         *   values are the network entities.
         */
        std::map<int,NetworkEntity*> networkEntities;
    };
}

#endif
