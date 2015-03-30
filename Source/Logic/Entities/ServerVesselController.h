#ifndef SERVERVESSELCONTROLLER_H
#define SERVERVESSELCONTROLLER_H

#include "ServerNetworkController.h"

class ServerVesselController: public ServerNetworkController
{
public:
    ServerVesselController();
    virtual ~ServerVesselController();
    virtual void onUpdate(Message msg);
};

#endif // SERVERVESSELCONTROLLER_H
