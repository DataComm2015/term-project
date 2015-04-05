#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

#define SPRITE_VERTICES 6
#define TILE_VERTICES 4
#define RECT_POINTS 4

class BGO;
class SGO;
class TGO;
namespace Marx
{
	class Map;
	class VEntity;
}

class Renderer
{
public:
	Renderer(sf::RenderTarget& renderTarget, unsigned int maxVertices = 1000 * SPRITE_VERTICES);

	~Renderer();

	void sf_draw(const sf::Drawable& drawable, const sf::RenderStates& states);
	void sf_draw(const sf::Vertex* vertices, unsigned int vertexCount,
		sf::PrimitiveType type, const sf::RenderStates& states);

	unsigned getDrawCallCount() const;
	unsigned getSpriteCount() const;

	void begin();
	void end();
	void resetStats();

	void draw(const BGO* bgo, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const SGO& sgo, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const TGO& tgo, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const Marx::Map& map, sf::RenderStates states = sf::RenderStates::Default);
	void draw(const Marx::VEntity& ve, sf::RenderStates states = sf::RenderStates::Default);

	sf::RenderStates states;

private:
	void mergeRenderStates(sf::RenderStates& toMerge) const;
	unsigned int prepareSpriteDrawing(const sf::Texture &texture);
	void batchSprite(const sf::Texture &texture, const sf::Vertex *vertices);
	void flushSprites();

	sf::RenderTarget &renderer;
	sf::Vertex *vertices;
	unsigned int maxCount, count;
	unsigned int count_drawcalls, count_cumulative;
	bool active;
};

#endif // RENDERER_H