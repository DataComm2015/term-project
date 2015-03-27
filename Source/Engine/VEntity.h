#ifndef VENTITY_H_
#define VENTITY_H_

#include "Entity.h"
#include "Controller.h"
#include <cmath>
#include "../Multimedia/graphics/object/SGO.h"

using namespace Marx;



class VEntity : public Entity
{
public:
	VEntity(SGO &_sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w) :
		sprite(_sprite), Entity(_map, x, y, ctrl, h, w)
	{
		const sf::FloatRect &bounds = sprite.sprite().getLocalBounds();
		sprite.sprite().setOrigin(bounds.width * 0.5f, bounds.height);
	}

	// this should get removed
	void update(const sf::Time& t) override
	{
		static float a = 0;
		static float b = 0.1;
		
		a += t.asSeconds();

		if(move( 45 + 10 * cos(a), 45 + 10 * sin(a), false))
		{
			b *= -1;
		}
	}

protected:
	void draw(Renderer& renderer, sf::RenderStates states) const override;

	SGO& sprite;
};

#endif