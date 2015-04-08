/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: VEntity.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--            VEntity(SGO & _sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w, ENTITY_TYPES eType = ENTITY_TYPES::I_DONT_KNOW);
--            sf::Transform getLocalTransform() const override;
--            const SGO& getSprite() const;
--            SGO& getSprite();
--            void setSprite(SGO& _sprite);
--
-- DATE: April 7, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- NOTES:
-- This class represents entities that are visible.
----------------------------------------------------------------------------------------------------------------------*/

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
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: Marx::VEntity::VEntity(SGO & _sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w,
--            ENTITY_TYPES eType)
--
-- NOTES:
-- VEntity constructor. Sets the sprite representing this Ventity and adds it to the specified map.
----------------------------------------------------------------------------------------------------------------------*/
Marx::VEntity::VEntity(SGO & _sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w, ENTITY_TYPES eType) :
Entity(_map, eType, x, y, ctrl, h, w)
{
	setSprite(_sprite);

	_map->add(*this);
	drawable = true;
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getLocalTransform
--
-- DATE: April 5, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: sf::Transform Marx::VEntity::getLocalTransform() const
--
-- NOTES:
-- Returns the transformations of this VEntity object. Converts its map position offset to world coordinates.
----------------------------------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getSprite
--
-- DATE: April 5, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: const SGO& Marx::VEntity::getSprite() const
--
-- NOTES:
-- Returns the const qualified sprite that's representing this VEntity object.
----------------------------------------------------------------------------------------------------------------------*/
const SGO& Marx::VEntity::getSprite() const
{
	return *sprite;
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getSprite
--
-- DATE: April 5, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: const SGO& Marx::VEntity::getSprite() const
--
-- NOTES:
-- Returns the sprite that's representing this VEntity object.
----------------------------------------------------------------------------------------------------------------------*/
SGO& Marx::VEntity::getSprite()
{
	return *sprite;
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setSprite
--
-- DATE: April 5, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: void Marx::VEntity::setSprite(SGO& _sprite)
--            _sprite: the new sprite
--
-- NOTES:
-- Sets the new sprite to be the one that will now represent this VEntity.
----------------------------------------------------------------------------------------------------------------------*/
void Marx::VEntity::setSprite(SGO& _sprite)
{
	sprite = &_sprite;
	const sf::FloatRect &bounds = sprite->sprite().getLocalBounds();
	sprite->sprite().setOrigin(bounds.width * 0.5, bounds.height);
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: draw
--
-- DATE: April 5, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
--            renderer: the renderer
--            states: the render states
--
-- NOTES:
-- Draws this entity by calling the matching draw method available inside of the Renderer class.
----------------------------------------------------------------------------------------------------------------------*/
void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
{
	if(drawable)
		renderer.draw(*this, states);
}
