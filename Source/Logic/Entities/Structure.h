#ifndef STRUCTURE_H_
#define STRUCTURE_H_


#include <SFML/Graphics.hpp>
#include "../../Engine/VEntity.h"
#include "../../Engine/Map.h"
#include "../../Engine/Cell.h"
#include "../../Engine/Controller.h"

class Structure : public Marx::VEntity
{
	public:
		Structure(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h, float w);
		virtual ~Structure();
		virtual void turn();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onUpdate();
		virtual bool operator==(const VEntity&);

	protected:
		Marx::Controller* _ctrl;
};

#endif
