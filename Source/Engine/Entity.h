/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Entity.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER:  Marc Vouve
--				Michael Chimick
--
-- NOTES:
--        This file defines the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/


#ifndef ENTITY_H_
#define ENTITY_H_

#include "Cell.h"
#include "Controller.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "Map.h"

#include <set>
#include <cmath>

namespace Marx
{
	class Entity : public sf::FloatRect, public BGO
	{
	protected:
		unsigned char blocking;	// can other entities pass through this entitiy? This can be set when an entity moves or by using setBlocking(short blocking)
		Controller * controller;
		std::set<Cell*> occupiedCells;
		Map * map;
	public:
		Entity(Map * _map, float x, float y, Controller * ctrl, float h, float w);
		virtual ~Entity();
		virtual void turn();
		Entity * move(float, float, bool);
		Entity * rMove(float, float, bool);
		Entity * aMove(float, float, bool);
		virtual std::set<Cell*> getCell();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onUpdate();
		setBlocking();
		virtual bool operator==(const Entity&);
	};
};
#endif
