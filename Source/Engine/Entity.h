/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:
--
-- PROGRAM:
--
-- FUNCTIONS:
--
-- DATE:
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- NOTES:
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
	    void Turn();
        Entity Move(float, float, bool);
        bool CheckCollision(Entity);
        std::set<Marx::Cell> GetCells();
        void OnCreate();
        void OnDestroy();
        void OnUpdate();

        bool operator==(const Entity&);
};

#endif