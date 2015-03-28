#include "ServerCommand.h"

#include <string.h>
#include "Entities/ServerCommandEntity.h"
#include "../Network/Message.h"
#include "ServerGameScene.h"

#include "Entities/PlayerEntity.h"
#include "Entities/ProperEntity.h"

using Networking::Message;

ServerCommand::ServerCommand(Scene *scene)
    : scene(scene)
{
}

void ServerCommand::onConnect(Session* session)
{
    printf("new connection\n");

    // create an entity that the new connection can use to communicate
    // commands to the server
    ServerCommandEntity* ctrlr = new ServerCommandEntity();
    PlayerEntity* player = new PlayerEntity(ctrlr);

    // create an entity that the client is supposed to control
    Marx::Map* cMap = ((ServerGameScene*)scene)->getcMap();
    new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ctrlr,1.0,1.0);

    // create an empty message because we need one
    Message msg;
    memset(&msg,0,sizeof(msg));

    // register the client with the player object, and player controller
    player->registerSession(session,msg);
    ctrlr->registerSession(session,msg);
}

void ServerCommand::onMessage(Session* session, char* data, int len)
{
}

void ServerCommand::onDisconnect(Session* session, int remote)
{
}
