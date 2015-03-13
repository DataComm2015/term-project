/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Entity.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Michael Chimick
--
-- NOTES:
--        This file defines the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/


#ifndef ENTITY_H_
#define ENTITY_H_
namespace Marx
{
    class Map;
}
#include "Cell.h"
#include "Controller.h"

#include <set>
#include <cmath>

namespace Marx
{
    class Entity : public sf::FloatRect
    {
        private:

            Controller * controller;
            std::set<Cell*> occupiedCells;
			Map * map;
        public:
            Entity(float, float, Controller *, float, float);
            ~Entity();
            virtual void turn();
            Entity * move(float, float, bool);
            virtual std::set<Cell*> getCell();
            virtual void onCreate();
            virtual void onDestroy();
            virtual void onUpdate();
            virtual bool operator==(const Entity&);
    };
}
#endif
