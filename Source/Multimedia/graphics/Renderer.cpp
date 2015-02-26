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
maxCount(maxSprites), count(0), cumulativeCount(0),
count_sprites(0), count_drawcalls(0),
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
	if (active) throw std::exception("Renderer is already active.");

	count_drawcalls = count = cumulativeCount = 0;
	states.texture = nullptr;
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
	if (!active) throw std::exception("Renderer is not active.");

	flush();
	active = false;

	count_sprites += cumulativeCount - count_sprites;
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
	if (!active) throw std::exception("Renderer is not active.");

	// Merge states

	if (states.blendMode == sf::RenderStates::Default.blendMode)
		states.blendMode = this->states.blendMode;
	//if (states.transform == sf::RenderStates::Default.transform)
	if (states.texture == sf::RenderStates::Default.texture)
		states.texture = this->states.texture;
	if (states.shader == sf::RenderStates::Default.shader)
		states.shader = this->states.shader;

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
	if (!active) throw std::exception("Renderer is not active.");

	// Combine transformations with this sprite's

	states.transform.combine(sgo().getTransform());

	// Store transformed vertices positions

	sf::Vector2f vPos[4];
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

	drawSprite(*sgo().getTexture(), vertices);
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
	if (!active) throw std::exception("Renderer is not active.");

	flush();

	sf_draw(tgo(), states);
}

/**
 * Draws the specified Map.
 *
 * @date       2015-02-25
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
void Renderer::draw(const Map& map, sf::RenderStates states)
{
	if (!active) throw std::exception("Renderer is not active.");

	// RENDER THE MAP :D
}

/**
 * Renders everything in the buffer.
 * Also "empties" the buffer.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 */
void Renderer::flush()
{
	if (count == 0) return;
	cumulativeCount += count;

	++count_drawcalls;
	renderer.draw(
		vertices,
		count * SPRITE_VERTICES,
		sf::PrimitiveType::Triangles,
		states
		);

	count = 0;
}

/**
 * Prepares the batcher for the next sprite.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      texture The upcoming texture to be used for the batch
 *
 * @return     The index of the first vertex to be used for the batch
 */
unsigned int Renderer::prepareSpriteDrawing(const sf::Texture &texture)
{
	if (!active) throw std::exception("Renderer is not active.");

	if (&texture != states.texture)
	{
		flush();
		states.texture = &texture;
	}
	else if (count >= maxCount)
	{
		flush();
	}

	return count++ * SPRITE_VERTICES;
}

/**
 * Draws the specified vertices that represent a sprite.
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
 * @param      texture  The texture to batch with
 * @param      vertices The array of vertices
 */
void Renderer::drawSprite(const sf::Texture &texture, const sf::Vertex *vertices)
{
	unsigned int idx = prepareSpriteDrawing(texture);

	sf::Vertex *ptr = &Renderer::vertices[idx];

	for (unsigned int vc = 0; vc < SPRITE_VERTICES; ++vc)
	{
		*ptr++ = *vertices++;
	}
}
