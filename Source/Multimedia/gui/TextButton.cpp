#include "TextButton.h"

/**
* Initializes a text button
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
TextButton(BGO* parent, sf::IntRect* theStates, std::function onClick, std::string theText)
{
    parent.add(this);
    states = theStates
    on_click = onClick;
    text = theText;
}

~TextButton()
{
    
}

/**
* sets the text in the button
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
void setText(std::string theText)
{
    text = theText;//not sure if this is right, TGO doesn't have a way to set text
}


/**
* sets the offset to the one give
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
void setOffset(sf::Vector2f theOffset)
{
    offset = theOffset;
}
void setFormat(int, bool, sf::Color)
{
    
}