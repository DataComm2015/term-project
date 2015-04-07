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

        //struct skill{
        //  float curX;
        //  float curY;
        //  int radius;
        //  int val;
        //  SKILLTYPE st;
        //};
        case PlayerCommandMsgType::SKILL:
        {
            Vessel *vessel = NULL;
            GateKeeper *keeper = NULL;
            skill *sk = ((skill*) msg.data);

            //for(int i = 0; i < 5; i++)
            //    printf("X: %f, Y: %f, Radius: %d, Value: %d\n", sk.curX, sk.curY, sk.radius, sk.val);

            float x1 = sk->curX;
            float y1 = sk->curY;
            float x2, y2;

            std::cout << "SKILL RECEIVED" << std::endl;
            auto entities = serverRef->getcMap()->getEntities();
            int i = 0;
            
            for(Entity *entity : entities)
            {
                i++;
                std::cout << "BEFOREIndex: " << i << std::endl;
                    
                if(entity->getType() == ENTITY_TYPES::VESSEL)
                {
                    vessel = dynamic_cast<Vessel*>((entity));
                    std::cout << "AFTERIndex: " << i << std::endl;
                    x2 = vessel->left;
                    y2 = vessel->top;

                    std::cout << "CHECKING " << std::endl;

                    std::cout << "x1 " << x1 << std::endl;

                    std::cout << "y1 " << y1 << std::endl;
                    std::cout << "x2 " << x2 << std::endl;

                    std::cout << "y2 " << y2 << std::endl;


                    std::cout << "Radius " << sk->radius << std::endl;

                    if (getDistance(x1, y1, x2, y2) <= sk->radius )
                    {
                        SkillEvent *ev = new SkillEvent(x1, y1, sk->radius, sk->val, sk->st);
                        std::cout << "DETECTED VESSEL WITHIN RADIUS" << std::endl;
                        std::cout << "Entity Health BEFORE: " << vessel->getHealth() << std::endl;
                        std::cout << "Entity VALUE: " << sk->val << std::endl;
                        //switch(sk->st)
                        //{
                        //    case SKILLTYPE::HEAL:
                        //        vessel->setHealth(vessel->getHealth() + sk->val);
                        //        vessel->getController()->addEvent(ev);
                        //    break;
                        //    case SKILLTYPE::DMG:
                        //        vessel->setHealth(vessel->getHealth() - sk->val);
                        //        vessel->getController()->addEvent(ev);
                        //    break;
                        //    case SKILLTYPE::BUFF:
                        //        vessel->setSpeed(vessel->getSpeed() + sk->val);
                        //        vessel->getController()->addEvent(ev);
                        //    break;
                        //    case SKILLTYPE::DEBUFF:
                        //        vessel->setSpeed(vessel->getSpeed() - sk->val);
                        //        vessel->getController()->addEvent(ev);
                        //    break;
                        //}
                        vessel->getController()->addEvent(ev);
                        std::cout << "Entity Health After: " << vessel->getHealth() << std::endl;

                        vessel = NULL;
                    }
                }
                else if(entity->getType() == ENTITY_TYPES::BASIC_TYPE)
                {
                    keeper = dynamic_cast<GateKeeper*>((entity));
                    std::cout << "AFTERIndex: " << i << std::endl;
                    x2 = keeper->left;
                    y2 = keeper->top;

                    std::cout << "CHECKING " << std::endl;

                    std::cout << "x1 " << x1 << std::endl;

                    std::cout << "y1 " << y1 << std::endl;
                    std::cout << "x2 " << x2 << std::endl;

                    std::cout << "y2 " << y2 << std::endl;


                    std::cout << "Radius " << sk->radius << std::endl;

                    if (getDistance(x1, y1, x2, y2) <= sk->radius )
                    {
                        SkillEvent *ev = new SkillEvent(x1, y1, sk->radius, sk->val, sk->st);
                        std::cout << "DETECTED VESSEL WITHIN RADIUS" << std::endl;
                        std::cout << "Entity Health BEFORE: " << keeper->getHealth() << std::endl;
                        std::cout << "Entity VALUE: " << sk->val << std::endl;
                        
                        std::cout << "Entity Health After: " << keeper->getHealth() << std::endl;
                        keeper->getController()->addEvent(ev);
                        

                        keeper = NULL;
                    }
                }
            }



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
