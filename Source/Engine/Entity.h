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
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- NOTES:
--        This file defines the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/

#ifndef STD_SET_
#define STD_SET_
#include <set>
#endif


#ifndef _CONTROLLER_H
#include "Controller.h"
#endif

#ifndef _CELL_H
#include "Cell.h"
#endif

#ifndef ENTITY_H_
#define ENTITY_H_

class Entity
{
    private:

        Controller controller;
        std::set<Marx::Cell> occupiedCells;

    public:

        Entity(Controller);
        ~Entity();
	    void turn();
        Entity move(float, float, bool);
        bool checkCollision(Entity);
        std::set<Marx::Cell> getCells();
        void onCreate();
        void onDestroy();
        void onUpdate();

        bool operator==(const Entity&);
};

#endif