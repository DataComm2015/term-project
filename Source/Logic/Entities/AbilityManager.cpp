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
	cMap = m;
}


/******************************************************************************
*	FUNCTION: getAbilityDetails
*
*	DATE: March 23, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: Ability getAbilityDetails(AbilityId id);
*
*	PARAMETERS:
*		id - the id of the ability to request
*
*	RETURNS:
*		Ability - an ability struct containing ability information
*
*	NOTES:
*		This function returns the information for a requested ability.
******************************************************************************/
Ability AbilityManager::getAbilityDetails(AbilityId id)
{
	Ability ability;
	ability.id = id;
	ability.cooldown = cooldowns[id];
	ability.name = names[id];
	ability.description = descriptions[id];
	ability.image = images[id];

	return ability;
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
*	RETURNS: bool - whether or not the cast succeeded
*
*	NOTES:
*		This function casts an ability on a specific coordinate in a map.
******************************************************************************/
bool AbilityManager::castAbility(int x, int y, AbilityId id)
{
	// If we are outside the borders of the map
	// if (x < 0 || x > cMap->getWidth() || y < 0 || y > cMap->getHeight())
	// {
	// 	return false;
	// }

	// Create the ability
	switch(id)
	{
		default:
		{
			// Invalid id selection
			return false;
		}
	}

	return true;
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
*	INTERFACE: bool castAbility(Entity *e, AbilityId id);
*
*	PARAMETERS:
*		e - the entity to cast on
*		id - the ability to cast
*
*	RETURNS: bool - whether or not the cast succeeded.
*
*	NOTES:
*		This function casts an ability on a specific entity.
******************************************************************************/
bool castAbility(Entity *e, AbilityId id)
{
	// Create the ability
	switch(id)
	{
		default:
		{
			// Invalid id selection
			return false;
		}
	}

	return true;
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