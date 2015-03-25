#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

#include "NetworkEntity.h"
#include "../Engine/ProperController.h"
namespace Networking
{

    class NetworkController : public ::Marx::ProperController, public NetworkEntity
    {
    public:
        NetworkController( int id, int type):NetworkEntity(id, type){}
        ~NetworkController();
        virtual void
        onUpdate( Message message );
        virtual void
        onRegister( int type, Session * session, Message message );
        virtual void
        onUnregister( Session * session, Message message );
        virtual void
        sendMoveUpdate(float x, float y, bool forced);

    private:
	void 
	parseMessage(Message& message);

    };
}

#endif
