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

using Networking::Client;

CommandEntity::CommandEntity(int id, GameScene* gameScene, ClientLobbyScene* lobbyScene)
    :NetworkEntity(id,NET_ENT_PAIR_PLAYER_COMMAND)
    ,_gameScene(gameScene)
    ,_lobbyScene(lobbyScene)
{
    _gameScene->addKeyListener(this);
}

CommandEntity::~CommandEntity()
{
    _gameScene->rmKeyListener(this);
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
    msg.type = command;
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

void CommandEntity::onUnregister(Session* session, Message msg)
{
    // Do Nothing
}

void CommandEntity::onUpdate(Message msg)
{
    switch(msg.type)
    {
    case MSG_T_PLAYER_COMMAND_START_GAME_SCENE:
        AppWindow::getInstance().removeScene(1);
        AppWindow::getInstance().setVerticalSyncEnabled(true);
        AppWindow::getInstance().addScene(_gameScene);
        AppWindow::getInstance().run();
        break;
    case MSG_T_PLAYER_COMMAND_START_LOBBY_SCENE:
        AppWindow::getInstance().removeScene(1);
        AppWindow::getInstance().setVerticalSyncEnabled(true);
        AppWindow::getInstance().addScene(_lobbyScene);
        AppWindow::getInstance().run();
        break;
    }
}
