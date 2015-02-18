#include "TGO.h"

#include "../renderer/Batch.h"

TGO::TGO() {}

TGO::~TGO() {}

sf::Text& TGO::operator()()
{
	return data;
}
const sf::Text& TGO::operator()() const
{
	return data;
}

const sf::Transform& TGO::getLocalTransform() const {
	return data.getTransform();
}

void TGO::middleAnchorPoint(bool arg) {
	if (arg) {
		const sf::FloatRect &bounds = data.getLocalBounds();
		data.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	}
	else data.setOrigin(0.f, 0.f);
}

void TGO::draw(Batch& batch, sf::RenderStates states) const {
	batch.draw(*this, states);
}