/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: EntityManager.h
--
-- PROGRAM:
--
-- FUNCTIONS:
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
--        This file defines the EntityManager class members
--
----------------------------------------------------------------------------------------------------------------------*/

#ifndef STD_VECTOR_
#define STD_VECTOR_
#include <vector>
#endif


#ifndef _ENTITY_H
#include "Entity.h"
#endif

#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

class EntityManager
{
    private:

	    std::vector<Entity> entities;

	public:
	
	    void Add( Entity );
	    void Remove( Entity );
	    void TakeTurn();
};

#endif