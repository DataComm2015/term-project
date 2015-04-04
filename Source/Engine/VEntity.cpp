#include "VEntity.h"
#include "Map.h"
#include "TileManager.h"

#include <iostream>

Marx::VEntity::VEntity(SGO & _sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w) :
sprite(_sprite), Entity(_map, x, y, ctrl, h, w)
{
	setSprite(_sprite);
	_map->add(*this);
}

const sf::Transform& Marx::VEntity::getLocalTransform() const
{
	{
		sf::FloatRect* tile = Manager::TileManager::get(map->getCell(0, 0)->getTileId());
	sf::Transform trans = sprite.sprite().getTransform();
	return trans.translate(
		left * tile->width + tile->width * 0.5, top * tile->height + tile->height
		);
}

const SGO& Marx::VEntity::getSprite() const
{
	return sprite;
}

void Marx::VEntity::setSprite(SGO& _sprite)
{
	sprite = _sprite;
	const sf::FloatRect &bounds = sprite.sprite().getLocalBounds();
	sprite.sprite().setOrigin(bounds.width * 0.5, bounds.height);
}

void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
{
	renderer.draw(*this, states);
}
