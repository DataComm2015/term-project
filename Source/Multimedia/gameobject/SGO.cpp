#include "SGO.h"

#include "../renderer/Batch.h"

/**
* Sprite Game Object.
*
* A BGO that represents a sprite.
*
* @author Melvin Loho
*/

SGO::SGO() {}

SGO::SGO(const sf::Texture& texture)
{
	data.setTexture(texture);
}

SGO::SGO(const sf::Texture& texture, const sf::IntRect& rect)
{
	data.setTexture(texture);
	data.setTextureRect(rect);
}

SGO::~SGO() {}

sf::Sprite& SGO::operator()()
{
	return data;
}
const sf::Sprite& SGO::operator()() const
{
	return data;
}

const sf::Transform& SGO::getLocalTransform() const {
	return data.getTransform();
}

void SGO::middleAnchorPoint(bool arg) {
	if (arg) {
		const sf::FloatRect &bounds = data.getLocalBounds();
		data.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	}
	else data.setOrigin(0.f, 0.f);
}

void SGO::draw(Batch& batch, sf::RenderStates states) const {
	batch.draw(*this, states);
}