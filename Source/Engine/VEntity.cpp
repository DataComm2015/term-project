#include "VEntity.h"
#include "Map.h"
#include "TileManager.h"

#include <iostream>

const sf::Transform& Marx::VEntity::getLocalTransform() const
{
	sf::FloatRect* tile = Manager::TileManager::get(map->getCell(0, 0)->getTileId());
	sf::Transform trans = sf::Transform::Identity;
	return trans.translate(left * tile->width, top * tile->height);
}

void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
{
	states.transform *= getLocalTransform();
	renderer.draw(sprite, states);
}
