#include "Projectile.h"

using namespace Marx;

Projectile::Projectile(float x, float y, Controller * ctrl = NULL, float h = 1.0, float w = 1.0, ProjectileManager &manager) :
	Entity(x, y, ctrl, h, w)
{
	_speed = 0;
	_manager = manager;
}

Projectile::~Projectile()
{
	_speed = 0;
	_manager.enqueue(this);
}

void Projectile::
setSpeed(float speed)
{
	_speed = speed;
}

Entity * Entity::move(float x, float y, bool force = false)
{

    std::set<Cell*> tempCell;
	// loop through collecting all cells that this entity will be contained in.
    for(int i = floor(x); i < width + floor(x); i++)
    {
        for(int j = floor(y); j < height + floor(y); j)
        {
            tempCell.emplace(map->getCell(floor(i),floor(j)));
        }
    }
	

	// loop through all cells in the temporary array. looping for 
    for(Cell *c : tempCell)
	{
		std::set<Entity*> entities = c->getEntity();
		for( Entity * e : entities )
		{
			if( intersects(*e) )
			{
				if( force )
				{
					occupiedCells = tempCell;
				}
				
				onHit(e);
			}
		}
	}
	
	occupiedCells = tempCell;
	
	return nullptr;
}

Entity* Projectile::onHit(Entity *entity)
{
	
	return nullptr;
}


