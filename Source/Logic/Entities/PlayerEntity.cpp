#include "PlayerEntity.h"

#include "../NetworkEntityPairs.h"
#include "../Event.h"

/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the.
 */

PlayerEntity::PlayerEntity(Controller* serverController)
    :NetworkEntity(NET_ENT_PAIR_PLAYER_COMMAND)
{
    this->serverController = serverController;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::onUnregister(Session* session, Message msg)
{
}

void PlayerEntity::onUpdate(Message msg)
{
    switch(msg.type)
    {
        case MSG_T_PLAYER_COMMAND_START_MV_LEFT_COMMAND:
        {
            MoveEvent event(-1,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND:
        {
            MoveEvent event(1,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND:
        {
            MoveEvent event(0,-1,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND:
        {
            MoveEvent event(0,1,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
    }
}
