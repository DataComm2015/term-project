#include "VEntity.h"
#include "Map.h"
#include "TileManager.h"

#include <iostream>

void Marx::VEntity::draw(Renderer& renderer, sf::RenderStates states) const
{
	std::cout << "vEntity's draw called" << std::endl;
	sf::FloatRect* tile = Manager::TileManager::get(map->getCell(0, 0)->getTileId());
	states.transform.translate(left * tile->width, (top + height) * tile->height);

	renderer.draw(sprite, states);
}
