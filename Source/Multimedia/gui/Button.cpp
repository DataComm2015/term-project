#include "Button.h"

/**
* Initializes a button with the states and the function when clicked.
*
* @date         2015-02-27
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       initializer
*/
Button::Button(BGO* parent, sf::IntRect* theStates, std::function onClick)
{
    parent.add(this);
    toggleEnabled = false;
    states = theStates;
    on_click = onClick;
}

/**
* Enables the toggling of the button based on the 'enabled' given
*
* @date         2015-02-27
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       void
*/
inline void Button::toggleEnabled(bool enabled)
{
    toggleEnabled = enabled;
}

/**
* Updates the button
*
* @date         2015-02-27
*
* @revisions
*
* @designer     
*
* @programmer   Jonathan Chu
*
* @return       void   
*/
void Button::update(sf::Time& t)
{
    
}
