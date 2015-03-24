#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

#include "NetworkEntity.h"
#include "../Engine/Controller.h"
namespace Networking
{
    //class NetworkEntityMultiplexer;
    //class Session;
    //class Message;

    class NetworkController : Controller, NetworkEntity
    {
   // friend class Session;
    //friend class NetworkEntityMultiplexer;
    public:
        /**
         * Constructs a new NetworkController.
         *
         * @param id the id used when multiplexing and demultiplexing
         * @param type denotes which sub class of NetworkEntity this entity is
         */
        NetworkController( int id, int type, NetworkEntityMultiplexer * mux ):NetworkEntity(id, type, mux){};

        /**
         * Destructs a NetworkController.
         */
        ~NetworkController();

        /**
         * Meant to be overwritten by user to handle an incoming update
         *
         * @param message message sent from the other side
         */
        virtual void
        onUpdate( Message message );


        /**
         * Meant to be overwritten by user. Called when the associated entity on
         * the other side calls the register method. MUST CALL silentRegister();
         *
         * @param session session that has been registered to the entity
         * @param message message that sent from the other side
         */
        virtual void
        onRegister( int type, Session * session, Message message );

        /**
         * Meant to be overwritten by the user. Called when the associated
         * entity on the other side calls the unregister method.
         * MUST CALL silentUnregister();
         *
         * @param session session that has been unregistered from the entity
         * @param message message that sent from the other side
         */
        virtual void
        onUnregister( Session * session, Message message );

    private:
	/**
         * Takes a messages and adds it to the event queue of this NetworkController
	 *
         * @param message message that sent from the other side
         */
	void 
	parseMessage(Message& message);

    };
}

#endif
