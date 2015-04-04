#include "Deity.h"
#include "../Event.h"

#include <iostream>

Deity::Deity(Marx::Map * gmap, float x, float y, Marx::Controller* controller, AbilityId one, AbilityId two)
    : Max::Entity(gmap, x, y, controller)
{
    abilityMan = AbilityManager::getInstance(gmap);
    oneId = one;
    twoId = two;
    
    std::cout << "Deity constructed successfully" << std::endl;
}

void Deity::onUpdate()
{
    std::vector<Marx::Event*> *eventQueue = getController()->getEvents();
    for(std::vector< Marx::Event*>::iterator it = eventQueue->begin(); it != eventQueue->end(); it++)
	{
		// switch on type
		switch((*it)->type)
		{
			case ::Marx::MOVE:
				MoveEvent* ev = (MoveEvent*) (*it);
                int xDir = ev->getXDir();
                int yDir = ev->getYDir();

                movingLeft = (xDir < 0);
                movingRight = (xDir > 0);
                movingUp = (yDir < 0);
                movingDown = (yDir > 0);
			break;
		}
	}
	getController()->clearEvents();

    float newXSpeed = 0.0;
    float newYSpeed = 0.0;

	if (movingLeft)
        newXSpeed = -xSpeed;
    else if (movingRight)
        newXSpeed = xSpeed;

    if (movingUp)
        newYSpeed = -ySpeed;
    else if (movingDown)
        newYSpeed = ySpeed;

    if (isMoving())
    {
        Entity::rMove(newXSpeed, newYSpeed,false);
    }
}

