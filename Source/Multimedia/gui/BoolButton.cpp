#include "BoolButton.h"

/**
* Initializes a Bool Button
*
* @date         2015-02-28
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       initializer
*/
BoolButton::BoolButton(BGO* parent, sf::IntRect* theStates, std::function onClick, SGO* toCheck, bool theState)
{
    parent.add(this);
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


