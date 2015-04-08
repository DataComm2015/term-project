#include "PlayerEntity.h"

#include "../GateKeeperSource/src/GateKeeper.h"
#include "../NetworkEntityPairs.h"
#include "../Event.h"
#include "../Skills.h"
#include "../ServerCommand.h"
#include "../Creature.h"
#include "ServerNetworkController.h"
#include "ServerGameState.h"
#include "../EntityTypes.h"

#include <cstdio>
#include <iostream>
#include <stdlib.h>

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
	vessel = NULL;
	points = 0.0F;
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

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	setType
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE:	void PlayerEntity::setType(PLAYER_TYPE type)
-- PLAYER_TYPE type: the type of PlayerEntity this is
--
-- RETURNS: 	void
--
-- NOTES:       Sets the player type (Warrior or Shaman, Life or Death) for the PlayerEntity.
--              Part of the function chain that propagates menu selection from lobby to game field.
-----------------------------------------------------------------------------------------------*/
void PlayerEntity::setType(PLAYER_TYPE type)
{
    this->type = type;
}

PLAYER_MODE PlayerEntity::getMode()
{
    return mode;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	getType
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE:	PLAYER_TYPE PlayerEntity::getType()
--
-- RETURNS: 	PLAYER_TYPE
--
-- NOTES:       Gets the player type (Warrior or Shaman, Life or Death) for the PlayerEntity.
--              Part of the function chain that propagates menu selection from lobby to game field.
-----------------------------------------------------------------------------------------------*/
PLAYER_TYPE PlayerEntity::getType()
{
    return type;
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
            switch( lobbyChoices.vesselChoice )
            {
              case 1:
                this->setType(PLAYER_TYPE::WARRIOR);
                break;
              case 2:
                this->setType(PLAYER_TYPE::SHAMAN);
                break;
            }
            server->getGameState()->notifyReadyForGame();

            break;
        }

        case PlayerCommandMsgType::SERVER_SELECTED_NICKNAME:
        {

            char* username = new char[16];
            memcpy(username, msg.data, strlen((char*)msg.data) + 1);
            nickname = username;
            fprintf(stdout, "PLAYER USERNAME: %s\n", username);
            fprintf(stdout, "PLAYER NICKNAME: %s\n", nickname);
            fflush(stdout);

            break;
        }

        case PlayerCommandMsgType::SKILL:
        {
            skillCaseHandler(msg);

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

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: skillCaseHandler
--
-- DATE: April 5, 2015
--
-- REVISIONS: Calvin Rempel - April 7, 2015
--              -> Randomized enemy spawns
--
-- DESIGNER: Julian Brandrick, Alex Lam
--
-- PROGRAMMER: Julian Brandrick, Alex Lam
--
-- INTERFACE: void skillCaseHandler(Message msg)
--
-- PARAMETERS:
--      msg -> The message received from the player.
--
-- NOTES:
--  This function handles all skill messages passed to the server.
----------------------------------------------------------------------------------------------------------------------*/
void PlayerEntity::skillCaseHandler(Message msg)
{
    Vessel *vessel = NULL;
    GateKeeper *keeper = NULL;

    // Retrieving the skills struct from the message
    skill *sk = ((skill*) msg.data);

    // If the skill type is a spawn, randomize spawned enemy
    if (sk->st == SKILLTYPE::SPAWN)
    {
        int enemyType = rand() % 4;
        ENTITY_TYPES type;
        switch (enemyType)
        {
            case 0:
                type = BASIC_TYPE;
                break;
            case 1:
                type = MINION;
                break;
            case 2:
                type = MINI_BOSS;
                break;
            default:
                type = MINI_BEE;
                break;
        }
        serverRef->createEnemy(type, NULL, sk->curX, sk->curY);

        givePoints(30.0);

        // Send the notification to all clients
        sendNotification(sk);
        return;
    }

    float x1 = sk->curX;
    float y1 = sk->curY;
    float x2, y2;

    std::cout << "SKILL RECEIVED" << std::endl;
    auto entities = serverRef->getcMap()->getEntities();

    // For each entity on the map, check to see if it was affected by the skill
    for(Entity *entity : entities)
    {
        // If the entity is a vessel
        if(entity->getType() == ENTITY_TYPES::VESSEL)
        {
            vessel = dynamic_cast<Vessel*>((entity));
            x2 = vessel->left;
            y2 = vessel->top;

            std::cout << "CHECKING VESSEL" << std::endl;
            std::cout << "x1 " << x1 << std::endl;
            std::cout << "y1 " << y1 << std::endl;
            std::cout << "x2 " << x2 << std::endl;
            std::cout << "y2 " << y2 << std::endl;
            std::cout << "Radius " << sk->radius << std::endl;

            // If the entity was within the skill radius, add the skill event to its event queue and add points to the
            //  player
            if (getDistance(x1, y1, x2, y2) <= sk->radius )
            {
                SkillEvent *ev = new SkillEvent(x1, y1, sk->radius, sk->val, sk->st);
                std::cout << "DETECTED VESSEL WITHIN RADIUS" << std::endl;
                std::cout << "Entity Health: " << vessel->getHealth() << std::endl;
                std::cout << "Entity VALUE: " << sk->val << std::endl;

                vessel->getController()->addEvent(ev);

                givePoints(15.0);

                vessel = NULL;
            }
        }
        // Else if the entity is a gatekeeper
        else if(entity->getType() == ENTITY_TYPES::BASIC_TYPE)
        {
            keeper = dynamic_cast<GateKeeper*>((entity));
            x2 = keeper->left;
            y2 = keeper->top;

            std::cout << "CHECKING GATEKEEPER" << std::endl;
            std::cout << "x1 " << x1 << std::endl;
            std::cout << "y1 " << y1 << std::endl;
            std::cout << "x2 " << x2 << std::endl;
            std::cout << "y2 " << y2 << std::endl;
            std::cout << "Radius " << sk->radius << std::endl;

            // If the entity was within the skill radius, add the skill event to its event queue and add points to the
            //  player
            if (getDistance(x1, y1, x2, y2) <= sk->radius )
            {
                SkillEvent *ev = new SkillEvent(x1, y1, sk->radius, sk->val, sk->st);
                std::cout << "DETECTED VESSEL WITHIN RADIUS" << std::endl;
                std::cout << "Entity Health: " << keeper->getHealth() << std::endl;
                std::cout << "Entity VALUE: " << sk->val << std::endl;

                keeper->getController()->addEvent(ev);

                givePoints(15.0);

                keeper = NULL;
            }
        }
    }

    std::cout << "POINTS: " << getPoints() << std::endl;

    // Send the notification to all clients
    sendNotification(sk);
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendNotification
--
-- DATE: April 5, 2015
--
-- REVISIONS: Calvin Rempel - April 7, 2015
--              -> Randomized enemy spawns
--
-- DESIGNER: Julian Brandrick, Alex Lam
--
-- PROGRAMMER: Julian Brandrick, Alex Lam
--
-- INTERFACE: void sendNotification(skill *sk)
--
-- PARAMETERS:
--      sk -> The skill structure containing the notification to send
--
-- NOTES:
--  Sends a skill notification to all clients in the game.
----------------------------------------------------------------------------------------------------------------------*/
void PlayerEntity::sendNotification(skill *sk)
{
    auto players = server->getGameState()->getPlayers();

    for(auto entry = players.begin(); entry != players.end(); entry++)
    {
        PlayerEntity* playerEntity = entry->second;

        Message message;

        message.type = (int)PlayerCommandMsgType::SKILL_NOTIFY;
        message.data = (void*)sk;
        message.len  = sizeof(skill);
        playerEntity->update(message);
    }
}

char* PlayerEntity::getNickname()
{
    fprintf(stdout, "PLAYER NICKNAME: %s\n", nickname);
    fflush(stdout);
    return nickname;
}

float PlayerEntity::getDistance(float x1, float y1, float x2, float y2 )
{
  float result;

  result = std::abs( std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2) );

  return result;
}

void PlayerEntity::setSGameScene(ServerGameScene *ref)
{
    serverRef = ref;
}

void PlayerEntity::setVessel(Vessel *vessel)
{
	this->vessel = vessel;
}

Vessel *PlayerEntity::getVessel()
{
	return vessel;
}

void PlayerEntity::givePoints(float _points)
{
	std::cout << "Points:: got: " << _points << std::endl;
	points += _points;
	std::cout << "MOAR POINTS!! " << points << std::endl;
}

float PlayerEntity::getPoints()
{
	return points;
}
