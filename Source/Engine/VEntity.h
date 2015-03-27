#ifndef VENTITY_H_
#define VENTITY_H_

#include "Entity.h"
#include "Controller.h"
#include "../Multimedia/graphics/object/SGO.h"

using namespace Marx;



class VEntity : public Entity
{
public:
	VEntity(SGO &_sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w) :
		sprite(_sprite), Entity(_map, x, y, ctrl, h, w)
	{
		const sf::FloatRect &bounds = sprite().getLocalBounds();
		sprite().setOrigin(bounds.width * 0.5f, bounds.height);
	}

	void update(const sf::Time& t) override
	{
		static unsigned counter = 0;

		move(left + 0.1, top + 0.1, false);
	}

protected:
	void draw(Renderer& renderer, sf::RenderStates states) const override;

	SGO& sprite;
};

#endif