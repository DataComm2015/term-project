#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

#define SPRITE_VERTICES 6

class BGO;
class SGO;
class TGO;
class Map;

class Renderer
{
public:
	Renderer(sf::RenderTarget& renderTarget, unsigned int maxSprites = 1000);

	~Renderer();

	void sf_draw(const sf::Drawable& drawable, const sf::RenderStates& states);
	void sf_draw(const sf::Vertex* vertices, unsigned int vertexCount,
		sf::PrimitiveType type, const sf::RenderStates& states);

	unsigned getDrawCallCount() const;
	unsigned getSpriteCount() const;

	void begin();
	void end();

	void draw(const BGO& bgo, bool scenegraph, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const SGO& sgo, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const TGO& tgo, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const Map& map, sf::RenderStates states = sf::RenderStates::Default);

	sf::RenderStates states;

private:
	void flush();

	unsigned int prepareSpriteDrawing(const sf::Texture &texture);

	void drawSprite(const sf::Texture &texture, const sf::Vertex *vertices);

	sf::RenderTarget &renderer;
	sf::Vertex *vertices;
	unsigned int maxCount, count, cumulativeCount;
	unsigned int count_sprites, count_drawcalls;
	bool active;
};

#endif // RENDERER_H
