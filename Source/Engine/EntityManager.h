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