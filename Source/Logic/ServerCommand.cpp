#include "ServerCommand.h"

#include "NetworkEntityPairs.h"
#include <string.h>
#include "Entities/ServerCommandEntity.h"
#include "../Network/Message.h"
#include "../Multimedia/manager/ResourceManager.h"
#include "../Multimedia/graphics/object/SGO.h"
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

    // create an empty message because we need one
    Message msg;
    memset(&msg,0,sizeof(msg));

    // register the client with the player object, and player controller
    player->registerSession(session,msg);

    // create an entity that the client is supposed to control
    Marx::Map* cMap = ((ServerGameScene*)scene)->getcMap();

    // id_resource championSprite = Manager::TextureManager::store(
    //     Manager::TextureManager::load("Assets/Art/Player/Run/Body/vessel-run-sheet.png")
    //     );

    // SGO championSGO2;
    // championSGO2.sprite().setTexture(*Manager::TextureManager::get(championSprite));
    // championSGO2.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
    // championSGO2.sprite().setScale(2, 2);
    // championSGO2.middleAnchorPoint(true);
    // Entity* e = new Vessel(championSGO2,cMap,45,45,(::Marx::Controller*)ctrlr,1.0F,1.0F);

    // // create a message to tell client what kind of entity to make
    // int paramsLen = 10;
    // int* params = (int*) malloc(paramsLen);
    // msg.type = MSG_T_SERVERCONTROLLER_NETCONTROLLER_MAKE_VESSEL;
    // msg.data = params;
    // msg.len  = paramsLen;

    // params[0] = (*e->getCell().begin())->getX();

    ctrlr->registerSession(session,msg);
}

void ServerCommand::onMessage(Session* session, char* data, int len)
{
}

void ServerCommand::onDisconnect(Session* session, int remote)
{
}
