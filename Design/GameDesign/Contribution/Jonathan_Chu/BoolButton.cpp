#include "BoolButton.h"

/**
* Initializes a Bool Button
*
* @date         2015-02-28
*
* @revisions	2015-03-18 - Removed BGO parent from constructor
*
* @designer     
*
* @programmer   Jonathan Chu
*				Marc Rafanan
*
* @return       initializer
*/
BoolButton::BoolButton(sf::IntRect* theStates, std::function onClick, SGO* toCheck, bool theState)
{
    states = theStates;
    on_click = onClick;
    check = toCheck;
    state = theState;
}

/**
* Returns the state of the bool button
*
* @date         2015-02-28
*
* @revisions
*
* @designer     
*
* @programmer   Jonathan Chu
*
* @return       boolean
*/
bool BoolButton::getState() 
{
    return state;
}

/**
* Updates the bool Button
*
* @date         2015-02-28
*
* @revisions
*
* @designer     
*
* @programmer   Jonathan Chu
*
* @return       void
*/
void BoolButton::update(sf::Time& t)
{
}


