#include "ValueButton.h"

/**
* Initializes a value button
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
ValueButton::ValueButton(BGO* parent, sf::IntRect* decButton, Button* incButton, Button*, Label* theLabel, std::function theFunc, std::string theText, int theValue, int modBy)
{
    parent.add(this);
    label = theLabel;
    dec = decButton;
    inc = incButton;
    callback = theFunc;
    value = theValue
    mod_by = modBy;
}

ValueButton::~ValueButton()
{
    //need to know what this valueButton does
}


ValueButton::void setFormat(int, bool, sf::Color)
{
    
}

/**
* Gets the value on the value button
*
* @date         2015-02-28
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       int
*/
int ValueButton::getValue()
{
    return value;
}

/**
* It sets the value on the valueButton
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
void ValueButton::setValue(int requiredValue)
{
    value = requiredValue;
}