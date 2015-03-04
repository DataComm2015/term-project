#include "Container.h"

/**
* Initializes a container
*
* @date         2015-02-26
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       initializer
*/
Container::Container(BGO* parent, BGO* firstBGO, BGO* secondBGO, sf::Vector2f theScale, bool theOrientation)
{
    parent.add(this);
    A = firstBGO;
    B = secondBGO;
    scale = theScale;
    orientation = theOrientation
}

/**
* Sets the separator for the containers
*
* @date         2015-02-26
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       void
*/
void Container::setSeperator(SGO* theSeparator)
{
    separator = theSeparator
}

/**
* Sets the ratio of the container
*
* @date         2015-02-26
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       void
*/
void Container::setRatio(int theRatio)
{
    ratio = theRatio;
}

/**
* Sets the orientation of the container
*
* @date         2015-02-26
*
* @revisions
*
* @designer   
*
* @programmer   Jonathan Chu
*
* @return       void
*/
void Container::setOrientation(bool theOrientation)
{
    orientation = theOrientation;
}

void Container::pack()
{
        //dont know what this is suppose to do
}
