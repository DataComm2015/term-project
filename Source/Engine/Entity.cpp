
#include "Entity.h"


Entity::Entity(Controller)
{
    // stuff
}

Entity::~Entity()
{
    // onDestroy
}

void Entity::turn()
{
    vector<int> events = controller.getEvents();
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
		Store all cells in the entities range in an set without duplicates
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
    
bool Entity::checkCollision( Entity e )
{
    vector<Cell> occupied_cells = e.getCells();

    for(unsigned int i = 0; i < occupiedCells.size(); i++)
    {
        if (i >= occupied_cells.size()) return false;

        if (occupiedCells.at(i) == occupied_cells.at(i)) return true;
    }

    return false;
}

vector<Cell> Entity::getCells()
{
    return occupiedCells;
}

bool Entity::operator==(Entity& entity)
{
    return false; // for now
}