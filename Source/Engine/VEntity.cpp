#include "VEntity.h"
#include "Map.h"
#include "TileManager.h"

#include <iostream>

const sf::Transform& Marx::VEntity::getLocalTransform() const
{
	sf::FloatRect* tile = Manager::TileManager::get(map->getCell(0, 0)->getTileId());
	sf::Transform trans = sprite.sprite().getTransform();
	return trans.translate(left * tile->width, (top + height) * tile->height);
}

void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
{
	renderer.draw(sprite, states);
}
