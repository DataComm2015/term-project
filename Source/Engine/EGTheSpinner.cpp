#include "EGTheSpinner.h"
#include <iostream>
using namespace Marx;

void TheSpinner::update(const sf::Time& t)
{
	Entity * e;

	theta += dir * t.asSeconds();

	if(e = move(midx + radius * cos(theta), midy + radius * sin(theta), false))
	{
		TheSpinner * v = dynamic_cast<TheSpinner*>(e);
		if( v != NULL )
		{
			v->dir *= -1;
		}
		dir *= -1;
	}
}
