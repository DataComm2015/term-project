#include "CommandEntity.h"

#include "../../AppWindow.h"

#include "../../Engine/Event.h"
#include "../../Engine/Controller.h"

#include "../Entities/ProperEntity.h"

#include "../GameScene.h"
#include "../Event.h"
#include "../NetworkEntityPairs.h"
#include "../ClientLobbyScene.h"
#include "../MainMenuScene.h"

#include "../ServerGameScene.h"
#include "../../Network/Client.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntityMultiplexer.h"

#include "ClientMux.h"

#include <cstdio>
#include <cstring>

using Networking::Client;

CommandEntity::CommandEntity(int id, ClientMux * client)
    :NetworkEntity(id,(int)NetworkEntityPair::PLAYER_COMMAND)
{
    clientmux = client;
    playerMode = PLAYER_MODE::GHOST;
}

CommandEntity::~CommandEntity()
{
}

void CommandEntity::attachListeners()
{
    MainMenuScene::getGameScene()->addKeyListener(this);
	MainMenuScene::getGameScene()->addClickListener(this);
}

PLAYER_MODE CommandEntity::getPlayerMode()
{
    return playerMode;
}

void CommandEntity::notifyServerLobbySelections(PlayerLobbyChoices *selections)
{
    PLC = selections;
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
            break;
		}
        case sf::Keyboard::Right:
		{
            command = (int)PlayerCommandMsgType::START_MV_RIGHT_COMMAND;
            break;
		}
        case sf::Keyboard::Up:
		{
            command = (int)PlayerCommandMsgType::START_MV_UP_COMMAND;
            break;
		}
        case sf::Keyboard::Down:
		{
            command = (int)PlayerCommandMsgType::START_MV_DOWN_COMMAND;
            break;
		}

        // bail out if we don't recognize the command
        default:
		{
            return;
		}
    }

    msg.type = command;
    msg.len  = sizeof(command);

    // send the command over the network
    update(msg);
}

void CommandEntity::onMouseClick(int key, int srcid, enum ActionType action, float xpos, float ypos)
{
    // convert keystroke into command
    int command;

	// put the command into a message to be sent over the network
    Message msg;

    switch(key)
    {
        case sf::Mouse::Left:
		{
            command = (int)PlayerCommandMsgType::START_ATT_COMMAND;
			AttackMessage attack;
			attack.srcid = srcid;
			attack.action = action;
			attack.cellx = xpos;
			attack.celly = ypos;
			msg.type = command;
			msg.data = &attack;
			msg.len  = sizeof(msg.type)+sizeof(AttackMessage);
            break;
		}
        case sf::Mouse::Right:
		{
            command = (int)PlayerCommandMsgType::START_SK_ATT_COMMAND;
			SkillAttackMessage sk_attack;
			sk_attack.srcid = srcid;
			sk_attack.action = action;
			sk_attack.destx = xpos;
			sk_attack.desty = ypos;
			msg.type = command;
			msg.data = &sk_attack;
			msg.len  = sizeof(msg.type)+sizeof(SkillAttackMessage);
            break;
		}

        // bail out if we don't recognize the command
        default:
		{
            return;
		}
    }


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
    fprintf(stdout, "THIS: %s\n", clientmux->message.data);
    fflush(stdout);
    update(clientmux->message);
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
        case PlayerCommandMsgType::SKILL_NOTIFY:
            skill *sk = (skill*)msg.data;

            MainMenuScene::getGameScene()->addSkillNotification(sk->curX, sk->curY, 3000, sk->st);
        break;
    }
}

PlayerLobbyChoices* CommandEntity::getLobbyOption()
{
    return PLC;
}

void CommandEntity::SendSkill(float curX, float curY, int radius, int value, SKILLTYPE st)
{
	skill a;

	a.curX = curX;
	a.curY = curY;
	a.radius = radius;
	a.val = value;
	a.st = st;

  // put the command into a message to be sent over the network
  Message msg;
  msg.type = (int)PlayerCommandMsgType::SKILL;
  msg.data = &a;
  msg.len  = sizeof(a);

  // send the command over the network
  update(msg);
}
