#ifndef SERVERVESSELCONTROLLER_H
#define SERVERVESSELCONTROLLER_H

#include "ServerCommandEntity.h"

class ServerVesselController: public ServerCommandEntity
{
public:
    ServerVesselController();
    virtual ~ServerVesselController();
    virtual void onUpdate(Message msg);
};

#endif // SERVERVESSELCONTROLLER_H
