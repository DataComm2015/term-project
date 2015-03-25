#ifndef _VISIBLE_ENTITY_
#define _VISIBLE_ENTITY_

#include "Entity.h"
#include "../Multimedia/graphics/object/SGO.h"

namespace Marx
{
	class VisibleEntity : public Entity
	{
		public:
			Entity(SGO * _sprite, Map * _map, float x, float y, Controller * ctrl = NULL, float h = 1.0, float w = 1.0 ) : 
				sprite(_sprite), Entity( _map, x, y, ctrl, h, w ){};
		protected:
			SGO * sprite;
	}
}

#endif