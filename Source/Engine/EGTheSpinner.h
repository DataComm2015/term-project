#ifndef THESPINNER_H_
#define THESPINNER_H_

#include "Entity.h"
#include "VEntity.h"

using namespace Marx;



class TheSpinner : public VEntity
{
public:
	TheSpinner(SGO &_sprite, Map * _map, float x, float y, float rad, float direct) :
		VEntity(_sprite, _map, x, y, NULL, 1, 1), radius(rad), theta(0), dir(direct), midx(x), midy(y)
	{
	}

	// this should get removed
	void update(const sf::Time& t);

protected:
	float radius;
	float theta;
	float dir;
	float midx;
	float midy;
};

#endif
