/**
 * A multipurpose renderer.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @notes      This renderer features:
 *             > All basic game object rendering
 *             > Sprite batching
 *             > Map rendering
 */

#include "Renderer.h"

#include "object/BGO.h"
#include "object/SGO.h"
#include "object/TGO.h"

#include "../manager/ResourceManager.h"
#include "../../Engine/TextureManager.h"
#include "../../Engine/TileManager.h"
#include "../../Engine/Map.h"

/**
 * Constructor.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      renderer   The render target (e.g. a window / a texture)
 * @param      maxSprites The maximum number of sprites the batcher can hold before it has to render them
 */
Renderer::Renderer(sf::RenderTarget &renderer, unsigned int maxSprites) :
renderer(renderer),
vertices(new sf::Vertex[maxSprites * SPRITE_VERTICES]),
maxCount(maxSprites), count(0),
count_drawcalls(0), count_sprites(0),
active(false)
{
	for (unsigned int v = 0; v < maxSprites * SPRITE_VERTICES; ++v)
	{
		vertices[v] = sf::Vertex();
	}
}

/**
 * Destructor.
 */
Renderer::~Renderer()
{
	delete[] vertices;
}

////////////////////////////////////////////////////////////
/// Wrapper for SFML's draw method.
/// \brief Draw a drawable object to the render-target
///
/// \param drawable Object to draw
/// \param states   Render states to use for drawing
///
////////////////////////////////////////////////////////////
void Renderer::sf_draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default)
{
	++count_drawcalls;
	renderer.draw(drawable, states);
}

////////////////////////////////////////////////////////////
/// Wrapper for SFML's draw method.
/// \brief Draw primitives defined by an array of vertices
///
/// \param vertices    Pointer to the vertices
/// \param vertexCount Number of vertices in the array
/// \param type        Type of primitives to draw
/// \param states      Render states to use for drawing
///
////////////////////////////////////////////////////////////
void Renderer::sf_draw(const sf::Vertex* vertices, unsigned int vertexCount,
	sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default)
{
	++count_drawcalls;
	renderer.draw(vertices, vertexCount, type, states);
}

/**
 * Gets the amount of draw calls made since the last rendering.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The number of draw calls
 */
unsigned Renderer::getDrawCallCount() const
{
	return count_drawcalls;
}

/**
 * Gets the amount of sprites drawn since the last rendering.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The number of sprites drawn
 */
unsigned Renderer::getSpriteCount() const
{
	return count_sprites;
}

/**
 * Starts and activates the renderer.
 * Resets all statistics and variables.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 */
void Renderer::begin()
{
	if (active) throw std::string("Renderer is already active.");

	count = 0;
	states = sf::RenderStates::Default;
	active = true;
}

/**
 * Ends and deactivates the renderer.
 * Renders everything not rendered yet.
 * Updates all statistics.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 */
void Renderer::end()
{
	if (!active) throw std::string("Renderer is not active.");

	flushSprites();
	active = false;
}

/**
* Resets the statistics of the renderer.
*
* @date       2015-02-28
*
* @revisions
*
* @designer   Melvin Loho
*
* @programmer Melvin Loho
*/
void Renderer::resetStats()
{
	count_drawcalls = count_sprites = 0;
}

/**
 * The general draw call for any kind of game object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      go         The game object to draw
 * @param      scenegraph Whether to draw the whole hierarchy or just the specified game object
 * @param      states     The render states
 */
void Renderer::draw(const BGO &go, bool scenegraph, sf::RenderStates states)
{
	if (!active) throw std::string("Renderer is not active.");

	mergeRenderStates(states);

	scenegraph ? go.drawSG(*this, states) : go.draw(*this, states);
}

/**
 * Draws the specifies SGO.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      sgo    The specified SGO
 * @param      states The render states
 */
void Renderer::draw(const SGO &sgo, sf::RenderStates states)
{
	if (!active) throw std::string("Renderer is not active.");

	// Combine transformations with this sprite's

	states.transform.combine(sgo().getTransform());

	// Store transformed vertices positions

	sf::Vector2f vPos[RECT_POINTS];
	sf::FloatRect sgoLB = sgo().getLocalBounds();

	vPos[0] = states.transform.transformPoint(sgoLB.left, sgoLB.top);
	vPos[1] = states.transform.transformPoint(sgoLB.left, sgoLB.top + sgoLB.height);
	vPos[2] = states.transform.transformPoint(sgoLB.left + sgoLB.width, sgoLB.top);
	vPos[3] = states.transform.transformPoint(sgoLB.left + sgoLB.width, sgoLB.top + sgoLB.height);

	// Create appropriate vertices

	sf::Vertex vertices[SPRITE_VERTICES];
	sf::IntRect texRect = sgo().getTextureRect();

	vertices[0].position = vPos[0];	vertices[2].position = vPos[2];
	vertices[1].position = vPos[1];	vertices[3].position = vPos[2];
	vertices[5].position = vPos[1];	vertices[4].position = vPos[3];

	for (unsigned int v = 0; v < SPRITE_VERTICES; v++) vertices[v].color = sgo().getColor();

	vertices[0].texCoords = { static_cast<float>(texRect.left), static_cast<float>(texRect.top) };
	vertices[1].texCoords = { static_cast<float>(texRect.left), static_cast<float>(texRect.top + texRect.height) };
	vertices[2].texCoords = { static_cast<float>(texRect.left + texRect.width), static_cast<float>(texRect.top) };
	vertices[3].texCoords = vertices[2].texCoords;
	vertices[4].texCoords = { static_cast<float>(texRect.left + texRect.width), static_cast<float>(texRect.top + texRect.height) };
	vertices[5].texCoords = vertices[1].texCoords;

	// Send vertices and texture

	batchSprite(*sgo().getTexture(), vertices);
}

/**
 * Draws the specified TGO.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      tgo    The specified TGO
 * @param      states The render states
 */
void Renderer::draw(const TGO &tgo, sf::RenderStates states)
{
	if (!active) throw std::string("Renderer is not active.");

	flushSprites();

	sf_draw(tgo(), states);
}

/**
 * Draws the specified Map.
 *
 * @date       2015-02-27
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      map    The specified Map
 * @param      states The render states
 */
void Renderer::draw(const Marx::Map& map, sf::RenderStates states)
{
	if (!active) throw std::string("Renderer is not active.");

	flushSprites();

	mergeRenderStates(states);
	states.texture = Manager::TextureManager::get(map.getTexture());

	unsigned
		mapXCoord = 0,
		mapYCoord = 0;

	const unsigned
		mapWidth = map.getWidth(),
		mapHeight = map.getHeight();

	sf::FloatRect* tile = Manager::TileManager::get(map.getCell(mapXCoord, mapYCoord)->getId());
	const sf::Vector2f mapTileSize(tile->width, tile->height);

	sf::Vector2f vpos[RECT_POINTS];
	sf::Vertex vert[TILE_VERTICES];

	for (unsigned y = 0; y < mapHeight; ++y)
	{
		// FORWARDS!!

		for (unsigned x = 0; x < mapWidth; ++x)
		{
			tile = Manager::TileManager::get(map.getCell(x, y)->getId());

			vpos[0] = { mapXCoord * mapTileSize.x, mapYCoord * mapTileSize.y };
			vpos[1] = vpos[0]; vpos[1].y += mapTileSize.y;
			vpos[2] = vpos[0]; vpos[2].x += mapTileSize.x;
			vpos[3].y = vpos[1].y; vpos[3].x = vpos[2].x;

			vert[0].position = vpos[0]; vert[2].position = vpos[2];
			vert[1].position = vpos[1]; vert[3].position = vpos[3];

			vert[0].texCoords = { tile->left, tile->top };
			vert[1].texCoords = { tile->left, tile->top + tile->height };
			vert[2].texCoords = { tile->left + tile->width, tile->top };
			vert[3].texCoords = { tile->left + tile->width, tile->top + tile->height };

			for (unsigned int i = 0; i < TILE_VERTICES; ++i)
				vertices[mapYCoord * mapWidth + mapXCoord + i] = vert[i];

			++mapXCoord;
		}

		if (++y == mapHeight) break; // Odd number of rows!! :(

		// BACKWARDS!!

		std::vector<std::string> tempTileIDs;

		for (unsigned x = 0; x < mapWidth; ++x)
		{
			tempTileIDs.push_back(map.getCell(x, y)->getId());
		}

		for (int x = tempTileIDs.size() - 1; x >= 0; --x)
		{
			tile = Manager::TileManager::get(map.getCell(x, y)->getId());

			vpos[0] = { mapXCoord * mapTileSize.x, mapYCoord * mapTileSize.y };
			vpos[1] = vpos[0]; vpos[1].y += mapTileSize.y;
			vpos[2] = vpos[0]; vpos[2].x -= mapTileSize.x;
			vpos[3].y = vpos[1].y; vpos[3].x = vpos[2].x;

			vert[0].position = vpos[0]; vert[2].position = vpos[2];
			vert[1].position = vpos[1]; vert[3].position = vpos[3];

			vert[2].texCoords = { tile->left, tile->top };
			vert[3].texCoords = { tile->left, tile->top + tile->height };
			vert[0].texCoords = { tile->left + tile->width, tile->top };
			vert[1].texCoords = { tile->left + tile->width, tile->top + tile->height };

			for (unsigned int i = 0; i < TILE_VERTICES; ++i)
				vertices[mapYCoord * mapWidth + mapXCoord + i] = vert[i];

			--mapXCoord;
		}

		++mapYCoord;
	}

	sf_draw(vertices, mapWidth * mapHeight * TILE_VERTICES, sf::TrianglesStrip, states);
}

/**
 * Merges "toMerge" with this renderer's RenderStates.
 *
 * @date       2015-02-28
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      toMerge The RenderStates to merge
 */
void Renderer::mergeRenderStates(sf::RenderStates& toMerge) const
{
	if (toMerge.blendMode == sf::RenderStates::Default.blendMode)
		toMerge.blendMode = this->states.blendMode;
	//if (toMerge.transform == sf::Transform::Identity)
	if (toMerge.texture == sf::RenderStates::Default.texture)
		toMerge.texture = this->states.texture;
	if (toMerge.shader == sf::RenderStates::Default.shader)
		toMerge.shader = this->states.shader;
}

/**
 * Prepares the renderer to batch the next sprite.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      texture The upcoming texture to be used for the renderer
 *
 * @return     The index of the first vertex to be used for the renderer
 */
unsigned int Renderer::prepareSpriteDrawing(const sf::Texture &texture)
{
	if (!active) throw std::string("Renderer is not active.");

	if (&texture != this->states.texture)
	{
		flushSprites();
		this->states.texture = &texture;
	}
	else if (count >= maxCount)
	{
		flushSprites();
	}

	return count++ * SPRITE_VERTICES;
}

/**
 * Batches the array of vertices that represent a sprite.
 * (count = SPRITE_VERTICES)
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      texture  The texture associated with these vertices
 * @param      vertices The array of vertices
 */
void Renderer::batchSprite(const sf::Texture &texture, const sf::Vertex *vertices)
{
	unsigned int idx = prepareSpriteDrawing(texture);

	sf::Vertex *ptr = &Renderer::vertices[idx];

	for (unsigned int vc = 0; vc < SPRITE_VERTICES; ++vc)
	{
		*ptr++ = *vertices++;
	}
}

/**
* Renders all of the sprites in the buffer and "empties" it.
*
* @date       2015-02-25
*
* @revisions
*
* @designer   Melvin Loho
*
* @programmer Melvin Loho
*/
void Renderer::flushSprites()
{
	if (count == 0) return;
	count_sprites += count;

	sf_draw(
		vertices,
		count * SPRITE_VERTICES,
		sf::PrimitiveType::Triangles,
		states
		);

	count = 0;
}
