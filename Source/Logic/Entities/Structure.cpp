/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Structure.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--		Structure(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0);
--		Structure(int id, SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0);
--		~Structure();
--		void onUpdate();
--		void turn();
--		void onCreate();
--		void onDestroy();
--		bool operator==(const VEntity&);
--
-- DATE: April 4, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Chris Klassen
--
-- PROGRAMMER:  Chris Klassen
--
-- NOTES:
--        This file contains the Structure class implementation.
----------------------------------------------------------------------------------------------------------------------*/


#include "Structure.h"
#include "../../Engine/Entity.h"
#include "../NetworkEntityPairs.h"
#include <typeinfo>


/******************************************************************************
*	FUNCTION: Structure
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: Structure(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0);
*
*	PARAMETERS:
*		sprite - the sprite used by the structure
*		map - the map to assign the structure to
*		x - the x position to generate at
*		y - the y position to generate at
*		ctrl - the controller to use
*		h - the height of the structure
*		w - the width of the structure
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the primary constructor of the Struture class.
******************************************************************************/
Structure::Structure(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
    VEntity(sprite, map, x, y, ctrl, h, w), Networking::NetworkEntity((int)NetworkEntityPair::STRUCTURE_MIRROR)
{
  printf("CREATING STRUCTURE");
}


/******************************************************************************
*	FUNCTION: Structure
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: Structure(int id, SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0);
*
*	PARAMETERS:
*		id - the id of the structure
*		sprite - the sprite used by the structure
*		map - the map to assign the structure to
*		x - the x position to generate at
*		y - the y position to generate at
*		ctrl - the controller to use
*		h - the height of the structure
*		w - the width of the structure
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the secondary constructor of the Struture class.
******************************************************************************/
Structure::Structure(int id, SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
    VEntity(sprite, map, x, y, ctrl, h, w), Networking::NetworkEntity(id, (int)NetworkEntityPair::STRUCTURE_MIRROR)
{
  printf("CREATING STRUCTURE");
}


/******************************************************************************
*	FUNCTION: ~Structure
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: ~Structure();
*
*	PARAMETERS:
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the destructor for the Structure.
******************************************************************************/
Structure::~Structure()
{

}


/******************************************************************************
*	FUNCTION: onUpdate
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void onUpdate();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This is the on-update function for the Structure.
******************************************************************************/
void Structure::onUpdate()
{

}


/******************************************************************************
*	FUNCTION: turn
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void turn();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This is the turn function for the Structure.
******************************************************************************/
void Structure::turn()
{

}


/******************************************************************************
*	FUNCTION: onCreate
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void onCreate();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This is the on-create function for the Structure.
******************************************************************************/
void Structure::onCreate()
{

}


/******************************************************************************
*	FUNCTION: onDestroy
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void onDestroy();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This is the on-destroy function for the Structure.
******************************************************************************/
void Structure::onDestroy()
{

}


/******************************************************************************
*	FUNCTION: operator==
*
*	DATE: April 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: bool operator==(const VEntity&);
*
*	PARAMETERS:
*		const VEntity& - the entity to compare against
*
*	RETURNS:
*		bool - whether or not the structure is the same
*
*	NOTES:
*		This function compares two entities.
******************************************************************************/
bool Structure::operator==(const VEntity&)
{
  return true;
}
