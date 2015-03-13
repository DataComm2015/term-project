#ifndef TGO_H
#define TGO_H

#include "BGO.h"

class Renderer;

class TGO : public BGO
{
public:
	TGO();

	virtual ~TGO();

	sf::Text& operator()();
	const sf::Text& operator()() const;

	const sf::Transform& getLocalTransform() const override;

	void middleAnchorPoint(bool arg);

protected:
	void draw(Renderer& renderer, sf::RenderStates states) const override;

private:
	sf::Text data;
};

#endif // TGO_H
