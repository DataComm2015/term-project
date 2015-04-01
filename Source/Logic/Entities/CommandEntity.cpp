#include "CommandEntity.h"

#include "../../AppWindow.h"

#include "../../Engine/Event.h"
#include "../../Engine/Controller.h"

#include "../Entities/ProperEntity.h"

#include "../GameScene.h"
#include "../Event.h"
#include "../NetworkEntityPairs.h"
#include "../ClientLobbyScene.h"

#include "../../Network/Client.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntityMultiplexer.h"

#include <cstdio>
#include <cstring>

using Networking::Client;

CommandEntity::CommandEntity(int id, GameScene* gameScene)
    :NetworkEntity(id,(int)NetworkEntityPair::PLAYER_COMMAND)
    ,_gameScene(gameScene)
{
    _gameScene->addKeyListener(this);
	_gameScene->addClickListener(this);
    playerMode = PLAYER_MODE::GHOST;
}

CommandEntity::~CommandEntity()
{
    _gameScene->rmKeyListener(this);
	_gameScene->rmClickListener(this);
}

PLAYER_MODE CommandEntity::getPlayerMode()
{
    return playerMode;
}

void CommandEntity::notifyServerLobbySelections(PlayerLobbyChoices *selections)
{
    // put the command into a message to be sent over the network
    Message msg;
    msg.type = (int)PlayerCommandMsgType::SELECT_LOBBY_OPTIONS;
    msg.data = (void*)selections;
    msg.len  = sizeof(PlayerLobbyChoices);

    // send the command over the network
    update(msg);
}

void CommandEntity::onKeyPressed(int key)
{
    // convert keystroke into command
    int command;

	// put the command into a message to be sent over the network
    Message msg;
    

    switch(key)
    {
        case sf::Keyboard::Left:
		{
            command = (int)PlayerCommandMsgType::START_MV_LEFT_COMMAND;
			int tmp[5] = {-1,0,-1,0,0};
			msg.data = tmp;
            break;
		}
        case sf::Keyboard::Right:
		{
            command = (int)PlayerCommandMsgType::START_MV_RIGHT_COMMAND;
			int tmp[5] = {1,0,1,0,0};
			msg.data = tmp;
            break;
		}
        case sf::Keyboard::Up:
		{
            command = (int)PlayerCommandMsgType::START_MV_UP_COMMAND;
			int tmp[5] = {0,-1,0,-1,0};
			msg.data = tmp;
            break;
		}
        case sf::Keyboard::Down:
		{
            command = (int)PlayerCommandMsgType::START_MV_DOWN_COMMAND;
			int tmp[5] = {0,1,0,1,0};
			msg.data = tmp;
            break;
		}

        // bail out if we don't recognize the command
        default:
		{
            return;
		}
    }

    msg.type = command;
    msg.len  = sizeof(command)+(sizeof(int)*5);

    // send the command over the network
    update(msg);
}

void CommandEntity::onMouseClick(int key, int srcid, float xpos, float ypos)
{
    // convert keystroke into command
    int command;

	// put the command into a message to be sent over the network
    Message msg;
    struct attack_struct
	{
		int _srcid;
		float _xpos;
		float _ypos;
	} attack;

	attack._srcid = srcid;
	attack._xpos = xpos;
	attack._ypos = ypos;
	msg.data = &attack;

    switch(key)
    {
        case sf::Mouse::Left:
		{
            command = (int)PlayerCommandMsgType::START_ATT_COMMAND;
            break;
		}
        case sf::Mouse::Right:
		{
            command = (int)PlayerCommandMsgType::START_SK_ATT_COMMAND;
            break;
		}

        // bail out if we don't recognize the command
        default:
		{
            return;
		}
    }

  	msg.type = command;
	msg.len  = sizeof(command)+(sizeof(float)*2)+sizeof(int);

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
            command = (int)PlayerCommandMsgType::STOP_MV_LEFT_COMMAND;
            break;
        case sf::Keyboard::Right:
            command = (int)PlayerCommandMsgType::STOP_MV_RIGHT_COMMAND;
            break;
        case sf::Keyboard::Up:
            command = (int)PlayerCommandMsgType::STOP_MV_UP_COMMAND;
            break;
        case sf::Keyboard::Down:
            command = (int)PlayerCommandMsgType::STOP_MV_DOWN_COMMAND;
            break;

        // bail out if we don't recognize the command
        default:
            return;
    }

    // put the command into a message to be sent over the network
    Message msg;
    msg.type = command;
    msg.data = &command;
    msg.len  = sizeof(command);

    // send the command over the network
    update(msg);
}

void CommandEntity::onRegister(Session *session)
{
}

void CommandEntity::onUnregister(Session* session, Message msg)
{
    // Do Nothing
}

void CommandEntity::onUpdate(Message msg)
{
    switch ((PlayerCommandMsgType)msg.type)
    {
        case PlayerCommandMsgType::SET_MODE:
            playerMode = *((PLAYER_MODE*) msg.data);

            break;
    }
}
