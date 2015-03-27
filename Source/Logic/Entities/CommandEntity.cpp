#include "CommandEntity.h"

#include "Logic/Event.h"
#include "Logic/ProperEntity.h"
#include "Logic/NetworkEntityPairs.h"

#include "Engine/Controller.h"
#include "Network/Client.h"
#include "Network/Session.h"
#include "Network/NetworkEntityMultiplexer.h"

CommandEntity::Command(int id, GameScene *scene)
    : NetworkEntity(id,NET_ENT_PAIR_PLAYER_COMMAND), scene(scene)
{
    scene->addKeyListener(this);
}

CommandEntity::~Command()
{
    scene->rmKeyListener(this);
}

void CommandEntity::onKeyPressed(int key)
{
    // convert keystroke into command
    int command;
    switch(key)
    {
        case sf::Keyboard::Left:
            command = MSG_T_PLAYER_COMMAND_START_MV_LEFT_COMMAND;
            break;
        case sf::Keyboard::Right:
            command = MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND;
            break;
        case sf::Keyboard::Up:
            command = MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND;
            break;
        case sf::Keyboard::Down:
            command = MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND;
            break;

        // bail out if we don't recognize the command
        default:
            return;
    }

    // put the command into a message to be sent over the network
    Message msg;
    msg.type = 0;
    msg.data = &command;
    msg.len  = sizeof(command);

    // send the command over the network
    update(msg);
}

void CommandEntity::onKeyReleased(int key)
{
    // convert keystroke into command
    int command;
    switch(key)
    {
        case sf::Keyboard::Left:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND;
            break;
        case sf::Keyboard::Right:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND;
            break;
        case sf::Keyboard::Up:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND;
            break;
        case sf::Keyboard::Down:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND;
            break;

        // bail out if we don't recognize the command
        default:
            return;
    }

    // put the command into a message to be sent over the network
    Message msg;
    msg.type = 0;
    msg.data = &command;
    msg.len  = sizeof(command);

    // send the command over the network
    update(msg);
}

void CommandEntity::onUnregister(Session* session, Message message)
{
    // Do Nothing
}

void CommandEntity::onUpdate(Message message)
{
    // Do Nothing
}
