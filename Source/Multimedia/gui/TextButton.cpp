#include "TextButton.h"

/**
* Initializes a text button
*
* @date         2015-02-27
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
TextButton(sf::IntRect* theStates, std::function onClick, std::string theText)
{
    states = theStates
    on_click = onClick;
    text = theText;
}

/**
* The destructor for the text button
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

/**
* sets the format to the one give
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
void setFormat(int, bool, sf::Color)
{
    
}
