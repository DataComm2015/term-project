#include "PlayerEntity.h"

#include "../NetworkEntityPairs.h"
#include "../Event.h"
#include "../ServerCommand.h"
#include "ServerNetworkController.h"
#include "ServerGameState.h"

#include <cstdio>


/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 * 
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the.
 */

PlayerEntity::PlayerEntity(ServerCommand *server)
    : server(server), NetworkEntity((int)NetworkEntityPair::PLAYER_COMMAND)
{
    this->controller = 0;
    nickname = 0;
}

PlayerEntity::~PlayerEntity()
{
    delete controller;
    delete nickname;
}

void PlayerEntity::setMode(PLAYER_MODE mode)
{
    this->mode = mode;

    Message msg;
    msg.type = (int)PlayerCommandMsgType::SET_MODE;
    msg.data = (void*) &(this->mode);
    msg.len = sizeof(this->mode);

    update(msg);
}

PLAYER_MODE PlayerEntity::getMode()
{
    return mode;
}

void PlayerEntity::onUnregister(Session* session, Message msg)
{
    server->playerLeft(session);
}

/**
 *  Jeff Bayntun and Eric Tsang
 *
 * @brief PlayerEntity::clearControllerEvents
 * clears all events from
 */
void PlayerEntity::clearControllerEvents()
{
    controller->clearEvents();
}

void PlayerEntity::setController(ServerNetworkController* controller)
{
    this->controller = controller;
}

void PlayerEntity::unsetController()
{
    this->controller = 0;
}

void PlayerEntity::onUpdate(Message msg)
{
    switch((PlayerCommandMsgType)msg.type)
    {
        case PlayerCommandMsgType::SELECT_LOBBY_OPTIONS:
        {
            lobbyChoices = *((PlayerLobbyChoices*) msg.data);
            server->getGameState()->notifyReadyForGame();

            break;
        }

        case PlayerCommandMsgType::SERVER_SELECTED_NICKNAME:
        {
            
            char* username = new char[16];
            memcpy(username, msg.data, strlen((char*)msg.data));
            nickname = username;
            fprintf(stdout, "PLAYER USERNAME: %s\n", username);
            fprintf(stdout, "PLAYER NICKNAME: %s\n", nickname);
            fflush(stdout); 

            break;
        }

        // if the player entity doesn't understand the network message, it
        // forwards it to the controller which controls a vessel, or deity
        default:
        {
            if(controller)
            {
                controller->onUpdate(msg);
            }
            break;
        }
    }
}

char* PlayerEntity::getNickname()
{
    fprintf(stdout, "PLAYER NICKNAME: %s\n", nickname);
    fflush(stdout);
    return nickname;
}
