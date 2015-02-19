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

#include "Entity.h"


Entity::Entity(Controller)
{
    onCreate();
}

Entity::~Entity()
{
    onDestroy();
}

void Entity::Turn()
{
    std::set<int> events = controller.getEvents();
    // do something
}


/* Leaving this for marc
 *
// This is a bit codey for pseudo-code, but it's done very particular
// this function returns the entity collided with on failure and NULL on success.
Entity move(float x, float y, bool force = false )
{
    if( entity is 1 cell in size )
    {
		Store all cells in the entities range in an std::set without duplicates
        if( !force )	// This argument is passed to check if bounds checking is required
        {
            Check if any entities are overlapping.
			if( entities overlap )
				return other entity
        }
       
       assign collection of cells to this as its cells
        
        // remove from current.
        Remove Entity From Previous Location
        
		Assign Location and bounding location
    }
}*/
    
bool Entity::CheckCollision( Entity entity )
{
    std::set<Marx::Cell>::iterator i_1;
    std::set<Marx::Cell>::iterator i_2;
    std::set<Marx::Cell> occupied_cells = entity.getCells();
    i_2 = occupied_cells.begin();

    for (i_1 = occupiedCells.begin(); i_1 != occupiedCells.end(); i_1++)
    {
        if (i_2 == occupied_cells.end()) return false;

        if ((Marx::Cell)*i_1 == (Marx::Cell)*i_2) return true;

        i_2++;
    }

    return false;
}

std::set<Marx::Cell> Entity::GetCells()
{
    return occupiedCells;
}

bool Entity::operator==(const Entity& entity)
{
    return false; // for now
}


void Entity::Onreate()
{
	// logic team
}

void Entity::OnDestroy()
{
	// logic team
}

void Entity::OnUpdate()
{
	// logic
}