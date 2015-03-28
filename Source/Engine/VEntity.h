#ifndef VENTITY_H_
#define VENTITY_H_

#include "Entity.h"
#include "Controller.h"
#include <cmath>
#include "../Multimedia/graphics/object/SGO.h"


namespace Marx
{

	class VEntity : public Entity
	{
	public:
		VEntity(SGO &_sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w) :
			sprite(_sprite), Entity(_map, x, y, ctrl, h, w)
		{
			const sf::FloatRect &bounds = sprite.sprite().getLocalBounds();
			sprite.sprite().setOrigin(bounds.width * 0.5f, bounds.height);
			map->add(*this);
		}

		// this should get removed
		void setSprite(SGO& _sprite)
		{
			sprite = _sprite;
		}

	protected:
		void draw(Renderer& renderer, sf::RenderStates states) const override;

		SGO& sprite;
	};

};
#endif
