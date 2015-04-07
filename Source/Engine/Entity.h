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
#include "../Multimedia/graphics/object/BGO.h"
#include "Map.h"
#include "../Logic/EntityTypes.h"

#include <set>
#include <cmath>


namespace Marx
{
	class Controller;

	class Entity : public sf::FloatRect, public BGO
	{
	public:
		Entity(Map * _map, ENTITY_TYPES eType, float x, float y, Controller * ctrl, float h, float w);
		virtual ~Entity();
		virtual void turn();
		Entity * move(float, float, bool);
		Entity * rMove(float, float, bool);
		Entity * rMove(sf::Vector2f &, float, bool);
		Entity * aMove(float, float, bool);
		Controller *getController();
		virtual std::set<Cell*> getCell();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onUpdate(float);
		virtual bool operator==(const Entity&);
		void setBlocking(bool);
		bool getBlocking();
		Map * getMap();
		ENTITY_TYPES getType();
		
	protected:
		std::set<Cell*> occupiedCells;
		Map * map;
		bool blocking;
	private:
		Controller * controller;
		ENTITY_TYPES type;
	};
};
#endif
