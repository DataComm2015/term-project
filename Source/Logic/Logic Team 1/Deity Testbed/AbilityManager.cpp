#include "../../../Engine/Map.h"
#include "AbilityManager.h"

using namespace Marx;

AbilityManager* AbilityManager::instance = nullptr;


/******************************************************************************
*	FUNCTION: AbilityManager
*
*	DATE: March 23, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: AbilityManager(Map *m);
*
*	PARAMETERS:
*		m - the map to use when casting abilities
*
*	RETURNS:
*
*	NOTES:
*		This is the default constructor for the AbilityManager class.
******************************************************************************/
AbilityManager::AbilityManager(Map *m)
{
	map = m;
}


/******************************************************************************
*	FUNCTION: castAbility
*
*	DATE: March 23, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: bool castAbility(int x, int y, AbilityId id);
*
*	PARAMETERS:
*		x - the x coordinate of the cast
*		y - the y coordinate of the cast
*		id - the ability to cast
*
*	RETURNS:
*
*	NOTES:
*		This is the default constructor for the AbilityManager class.
******************************************************************************/
bool AbilityManager::castAbility(int x, int y, AbilityId id)
{
	
}


/******************************************************************************
*	FUNCTION: getInstance
*
*	DATE: March 23, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: AbilityManager* getInstance(Map *m);
*
*	PARAMETERS:
*		m - the map to pass in (only needed when first called)
*
*	RETURNS:
*		AbilityManager* - an instance of the class
*
*	NOTES:
*		This function returns an instance of the singleton class.
******************************************************************************/
AbilityManager* AbilityManager::getInstance(Map *m)
{
	// If we do not already have an instance
	if (instance == nullptr)
	{
		// Create a new instance
		instance = new AbilityManager(m);
	}

	return instance;
}