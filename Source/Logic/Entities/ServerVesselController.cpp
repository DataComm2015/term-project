#include "ServerVesselController.h"
#include "../NetworkEntityPairs.h"
#include "../Event.h"

ServerVesselController::ServerVesselController()
    : ServerNetworkController(NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
{
}

ServerVesselController::~ServerVesselController()
{
}

void ServerVesselController::onUpdate(Message msg)
{
    switch(msg.type)
    {
        case MSG_T_PLAYER_COMMAND_START_MV_LEFT_COMMAND:
        {
            MoveEvent event(-1,0,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND:
        {
            MoveEvent event(1,0,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND:
        {
            MoveEvent event(0,-1,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND:
        {
            MoveEvent event(0,1,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND:
        {
            MoveEvent event(0,0,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent event(0,0,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND:
        {
            MoveEvent event(0,0,0);
            addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND:
        {
            MoveEvent event(0,0,0);
            addEvent(event);
            break;
        }
    }
}
