#include "Session.h"
#include "NetworkEntity.h"

namespace Networking
{
    class NetworkEntityMultiplexer
    {
    public:
        /**
         * constructs a new {NetworkEntityMultiplexer}.
         */
        NetworkEntityMultiplexer();
        /**
         * method with the same signature as the Session::onMessage. this
         *   function should be invoked within the session's onMessage method
         *   and forwarded the parameters if the message received by the session
         *   was sent from another {NetworkEntityMultiplexer}.
         *
         * @param  msg message received from a session object.
         *
         * @return integer indicating the outcome of the operation
         */
        int onMessage(Message* msg);
    protected:
        /**
         * should only be called from within the Networking library. it creates
         *   a new NetworkEntity subclass instance, and returns it to the
         *   {NetworkEntityMultiplexer}.
         *
         * this method should be overriden to instantiate an instance of a
         *   subclass of the {NetworkEntity}, and return it.
         *
         * @param  id identifier associated with a {NetworkEntity} instance.
         * @param  entityType type of the entity, hinting at what kind of
         *   {NetworkEntity} sub class object to instantiate.
         * @param  session session being registered with the NetworkEntity.
         * @param  msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         */
        virtual NetworkEntity onRegister(
            int id, int entityType, Session* session, Message msg) = 0;
    private:
        /**
         * should only be called by {NetworkEntity} objects only. it
         *   encapsulates the passed data into a packet, to be sent to all
         *   session objects registered with the {NetworkEntity} associated with
         *   {id}.
         *
         * @param  id identifier associated with a {NetworkEntity} instance
         * @param  msg describes the message to send over the wire
         *
         * @return integer indicating the result of the operation
         */
        int update(int id, Message msg);
        /**
         * should only be called by the {NetworkEntity} class. it registers the
         *   passed {Session} object with the {NetworkEntity} associated with
         *   {id}, and sends the {msg} to the {session}.
         *
         * @param  id identifier associated with a {NetworkEntity} instance
         * @param  session {Session} to be registered with the {NetworkEntity}
         *   instance
         * @param  msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         *
         * @return integer indicating the result of the operation
         */
        int register(int id, Session* session, Message msg);
        /**
         * should only be invoked by the {NetworkEntity} class. it unregisters
         *   the {session} from the {NetworkEntity} instance associated with
         *   {id}, and sends the {msg} to the {session}.
         *
         * @param  id identifier associated with a {NetworkEntity} instance
         * @param  session {Session} to be unregistered with the {NetworkEntity}
         *   instance
         * @param  msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         *
         * @return integer indicating the result of the operation
         */
        int unregister(int id, Session* session, Message msg);
        /**
         * should only be called from within the Networking library. it calls
         *   the update method of the {NetworkEntity} instance associated with
         *   {id}.
         *
         * @param  id identifier associated with a {NetworkEntity} instance.
         * @param  msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         */
        void onUpdate(int id, Message msg);
        /**
         * should only be called from within the Networking library. it calls
         *   the onUnregister method of the {NetworkEntity} instance associated
         *   with {id}.
         *
         * @param  id identifier associated with a {NetworkEntity} instance.
         * @param  session session being registered with the NetworkEntity.
         * @param  msg describes the message to send over the wire. this message
         *   is only sent to the {session}.
         */
        void onUnregister(int id, Session* session, Message msg);
    };
}
