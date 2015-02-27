/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: World.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--          void setEntities(const vector<Entity*> entities);
--          void setLobby(const Lobby& lobby);
--          void setEntityManager(const EntityManager manager);
--          void setMap(const Map& map);
--          vector<Entity*> getEntities();
--          Lobby getLobby();
--          EntityManager getEntityManager();
--          Map getMap();
--
-- DATE: February 15, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- NOTES:
--      This file implements the World class members
----------------------------------------------------------------------------------------------------------------------*/

#include "World.h"

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setEntities
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setEntities(const vector<Entity*> entities)
--
-- PARAMETERS:
--     entities    -    entities in the game
--
-- RETURNS:
--     void
--
-- NOTES:
--     Setter for entities in the world
--
----------------------------------------------------------------------------------------------------------------------*/
//void World::setEntities(const vector<Entity*> entities)
//{
//    entities_ = entities;
//}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setLobby
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setLobby(const Lobby& lobby)
--
-- PARAMETERS:
--     lobby    -    lobby for the game
--
-- RETURNS:
--     void
--
-- NOTES:
--     Setter for lobby in the world
--
----------------------------------------------------------------------------------------------------------------------*/
void World::setLobby(const Lobby& lobby)
{
    lobby_ = lobby;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setEntityManager
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setEntityManager(const EntityManager& manager)
--
-- PARAMETERS:
--     manager    -    manager for the entities
--
-- RETURNS:
--     void
--
-- NOTES:
--     Setter for entity manager in the world
--
----------------------------------------------------------------------------------------------------------------------*/
//void World::setEntityManager(const EntityManager& manager)
//{
//    manager_ = manager;
//}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setMap
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setMap(const Map& map)
--
-- PARAMETERS:
--     map    -    map for the game
--
-- RETURNS:
--     void
--
-- NOTES:
--     Setter for map in the world
--
----------------------------------------------------------------------------------------------------------------------*/
void World::setMap(const Map& map)
{
    map_ = map;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEntities
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: vector<Entity*> getEntities()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     vector<Entity*>
--
-- NOTES:
--     Getter for entities in the world
--
----------------------------------------------------------------------------------------------------------------------*/
//vector<Entity*> World::getEntities()
//{
//    return entities_;
//}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getLobby
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: Lobby getLobby();
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     Lobby
--
-- NOTES:
--     Getter for lobby in the world
--
----------------------------------------------------------------------------------------------------------------------*/
Lobby World::getLobby()
{
    return lobby_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEntityManager
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: EntityManager getEntityManager()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     EntitryManager
--
-- NOTES:
--     Getter for entity manager in the world
--
----------------------------------------------------------------------------------------------------------------------*/
//EntityManager World::getEntityManager()
//{
//    return manager_;
//}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getMap
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: Map getMap()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     Map
--
-- NOTES:
--     Setter for map in the world
--
----------------------------------------------------------------------------------------------------------------------*/
Map World::getMap()
{
    return map_;
}