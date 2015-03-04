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

#include "Cell.h"
#include "Controller.h"

namespace Marx
{
    class Entity
    {
        private:

            Controller controller;
            std::set<Marx::Cell> occupiedCells;
            sf::FloatRect location;
        public:

            virtual Entity(Controller);
            virtual ~Entity();
            void turn();
            Entity move(float, float, bool);
            bool checkCollision(Entity);
            virtual std::set<Marx::Cell> getCells();
            virtual void onCreate();
            virtual void onDestroy();
            virtual void onUpdate();
            sf::FloatRect getRekt();
            void setRekt(sf::FloatRect);
            bool operator==(const Entity&);
    };
}
#endif
