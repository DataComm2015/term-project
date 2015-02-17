
#include "Entity.h"

class EntityManager
{
    private:

	    vector<Entity> entities;

	public:
	
	    void Add( Entity );
	    void Remove( Entity );
	    void TakeTurn();
};