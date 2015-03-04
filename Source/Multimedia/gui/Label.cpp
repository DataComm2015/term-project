
#include "label.h"

/**
* Initializes a label
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
Label::Label(BGO* parent, SGO* theBackground, std::string theText)
{
    parent.add(this);
    theBackground = false;
    background = theBackground;
    data = theText;
}

/**
* Toggles the background between on/off
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
void Label::toggleBackground(bool toggled)
{
    theBackground = toggled;
}

/**
* Sets the offset based on the offset given
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
void Label::setOffset(sf::Vector2f theOffset)
{
    offset = theOffset;
}