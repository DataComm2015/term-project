#include "VEntity.h"
#include "Map.h"
#include "TileManager.h"
#include "../Logic/Entities/Vessel.h"
#include <iostream>
#include "../Multimedia/graphics/Animation.h"


/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: VEntity
--
-- DATE: April 5, 2015
--
-- REVISIONS: Julian Brandrick - April 5, 2015
--				-> Added an entity type parameter and gave it the default type of I_DONT_KNOW
--
-- DESIGNER: 
--
-- PROGRAMMER: 
--
-- INTERFACE: Marx::VEntity::VEntity(SGO & _sprite, Map * _map, float x, float y
									, Controller * ctrl, float h, float w, ENTITY_TYPES eType)
--
-- NOTES:
--  
----------------------------------------------------------------------------------------------------------------------*/
Marx::VEntity::VEntity(SGO & _sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w, ENTITY_TYPES eType) :
Entity(_map, eType, x, y, ctrl, h, w)
{
	setSprite(_sprite);

	_map->add(*this);
	drawable = true;
}

sf::Transform Marx::VEntity::getLocalTransform() const
{
	sf::FloatRect* tile = Manager::TileManager::get(map->getCell(0, 0)->getTileId());
	sf::Vector2f mapPositionOffset(left * tile->width, top * tile->height);
	sf::Transform realtrans;

	sprite->sprite().move(mapPositionOffset);
	realtrans *= sprite->sprite().getTransform();
	sprite->sprite().move(mapPositionOffset * -1.f);

	return realtrans;
}

const SGO& Marx::VEntity::getSprite() const
{
	return *sprite;
}

SGO& Marx::VEntity::getSprite()
{
	return *sprite;
}

void Marx::VEntity::setSprite(SGO& _sprite)
{
	sprite = &_sprite;
	const sf::FloatRect &bounds = sprite->sprite().getLocalBounds();
	sprite->sprite().setOrigin(bounds.width * 0.5, bounds.height);
}

void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
{
	if(drawable)
		renderer.draw(*this, states);
}
