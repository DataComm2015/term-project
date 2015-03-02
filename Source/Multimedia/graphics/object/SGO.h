#ifndef SGO_H
#define SGO_H

#include "BGO.h"

class Renderer;

class SGO : public BGO
{
public:
	SGO();
	SGO(const sf::Texture& texture);
	SGO(const sf::Texture& texture, const sf::IntRect& rect);

	virtual ~SGO();

	sf::Sprite& operator()();
	const sf::Sprite& operator()() const;

	const sf::Transform& getLocalTransform() const override;

	void middleAnchorPoint(bool arg);

protected:
	void draw(Renderer& renderer, sf::RenderStates states) const override;

private:
	sf::Sprite data;
};

#endif // SGO_H
