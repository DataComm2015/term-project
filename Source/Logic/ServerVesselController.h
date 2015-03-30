#ifndef SERVERVESSELCONTROLLER_H
#define SERVERVESSELCONTROLLER_H

#include "Entities/ServerCommandEntity.h"
#include "NetworkEntityPairs.h"

class ServerVesselController: public ServerCommandEntity
{
public:
    ServerVesselController() : NetworkEntity(NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER){}
    virtual void onUpdate(Message msg);
    ~ServerVesselController();
};

#endif // SERVERVESSELCONTROLLER_H
