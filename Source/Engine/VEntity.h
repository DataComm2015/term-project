#ifndef VENTITY_H_
#define VENTITY_H_

#include "Entity.h"
#include "Controller.h"
#include "../Multimedia/graphics/object/SGO.h"

using namespace Marx;



	class VEntity : public Entity
	{
		public:
			VEntity(SGO &_sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w ) :
			sprite(_sprite), Entity(_map, x, y, ctrl, h, w){};
		protected:
			SGO sprite;
	};

#endif