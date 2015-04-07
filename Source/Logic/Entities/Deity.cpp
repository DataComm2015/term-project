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
		/*

    switch((*it)->type)
		{
			case ::Marx::SKILL:
        SkillEvent* ev = (SkillEvent*) (*it);
        ev->getX();
        ev->getY();

        id_resource img;


        switch(ev->getType())
        {
          case HEAL:
            img = ...;
          break;
          case HURT:
            img = ...;
          break;
          case BUFF:
            img = ...;
          break;
          case DEBUFF:
            img = ...;
          break;
        }

        SGO*  = ....

        //Add to gamescene vector of skill assets with duration of skill

			break;
		}

    */
	}
	getController()->clearEvents();
}
