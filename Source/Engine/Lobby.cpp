/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Lobby.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--          bool join(void* player)
--          bool leave(void* player)
--          bool joinable()
--          std::vector<void*> getPlayerQueue()
--          std::vector<void*> getSpectatorQueue()
--          bool getJoinBlock()
--          void setJoinBlock(bool state)
--
-- DATE: February 16, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- NOTES:
--      This file implements the Lobby class members
----------------------------------------------------------------------------------------------------------------------*/

#include "Lobby.h"

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: join
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: join(void *player)
--
-- PARAMETERS:
--     player    -    void pointer to a player entity defined by the network
--
-- RETURNS:
--     bool    -    true if player successfully joined, else false
--
-- NOTES:
--     Interface for the player to join the lobby
--
----------------------------------------------------------------------------------------------------------------------*/
bool Lobby::join(void* player)
{
    if(spectatorQueue_.size() < spectatorLimit_)
        spectatorQueue_.push_back(player);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: leave
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: leave(void *player)
--
-- PARAMETERS:
--     player    -    void pointer to a player entity defined by the network
--
-- RETURNS:
--     bool    -    true if player successfully joined, else false
--
-- NOTES:
--     Interface for the player to join the lobby
--
----------------------------------------------------------------------------------------------------------------------*/
bool Lobby::leave(void* player)
{
    // not sure how to compare players to remove in the queue yet.
    // might use an id for the player in the queue
    
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: joinable
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: bool Lobby::joinable()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     bool    -    true if lobby is joinable
--
-- NOTES:
--     Function to check if lobby is joinable
--
----------------------------------------------------------------------------------------------------------------------*/
bool Lobby::joinable()
{
    return (playerQueue_.size() < playerLimit_ && !joinBlock_) ? true : false;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getPlayerQueue
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: std::vector<void*> getPlayerQueue
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     std::vector<void*>    -    player queue
--
-- NOTES:
--     Gets player queue std::vector
--
----------------------------------------------------------------------------------------------------------------------*/
std::vector<void*> Lobby::getPlayerQueue()
{
    return playerQueue_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getSpectatorQueue
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: std::vector<void*> getSpectatorQueue
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     std::vector<void*>    -    spectator queue
--
-- NOTES:
--     Gets spectator queue std::vector
--
----------------------------------------------------------------------------------------------------------------------*/
std::vector<void*> Lobby::getSpectatorQueue()
{
    return spectatorQueue_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getJoinBlock
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: bool getJoinBlock
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     bool    -    joinBlock
--
-- NOTES:
--     Returns joinBlock_ state.
--
----------------------------------------------------------------------------------------------------------------------*/
bool Lobby::getJoinBlock()
{
    return joinBlock_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setJoinBlock
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setJoinBlock(bool state)
--
-- PARAMETERS:
--     state    -    set the joinBlock to state (bool)
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets joinBlock_
--
----------------------------------------------------------------------------------------------------------------------*/
void Lobby::setJoinBlock(bool state)
{
    joinBlock_ = state;
}