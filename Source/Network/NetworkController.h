#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

#include "NetworkEntity.h"
#include "../Engine/Controller.h"
namespace Networking
{

    class NetworkController : public ::Marx::Controller, public NetworkEntity
    {
    public:
        NetworkController(int id, int type):NetworkEntity(id,type){}
        NetworkController(int type):NetworkEntity(type){}
        ~NetworkController();
        virtual void onUpdate( Message message );
        virtual void onUnregister( Session * session, Message message );
    private:
        void parseEventMessage(Message& message);
        void sendEventMessage(Event ev);
    };
}

#endif
