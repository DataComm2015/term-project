#ifndef BATCH_H
#define BATCH_H

#include <SFML/Graphics.hpp>

#define SPRITE_VERTICES 6

class BGO;
class SGO;
class TGO;

/**
 * Batches count_sprites before rendering to increase performance.
 * Also takes in any kind of game objects for convenience.
 *
 * @author Melvin Loho
 */
class Batch
{
public:
	/**
	 * Constructor.
	 *
	 * @param renderer   the render target (e.g. a window / a texture)
	 * @param maxSprites the max number of count_sprites to batch
	 */
	Batch(sf::RenderTarget &renderer, unsigned int maxSprites = 1000);

	/**
	 * Destructor.
	 */
	~Batch();

	////////////////////////////////////////////////////////////
	/// Wrapper for SFML's draw method.
	/// \brief Draw a drawable object to the render-target
	///
	/// \param drawable Object to draw
	/// \param states   Render states to use for drawing
	///
	////////////////////////////////////////////////////////////
	void sf_draw(const sf::Drawable& drawable, const sf::RenderStates& states);

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
	void sf_draw(const sf::Vertex* vertices, unsigned int vertexCount,
		sf::PrimitiveType type, const sf::RenderStates& states);

	/**
	* Gets the amount of draw calls made since the last batching.
	*
	* @return the number of draw calls
	*/
	unsigned getDrawCallCount() const;

	/**
	* Gets the amount of count_sprites drawn since the last batching.
	*
	* @return the number of count_sprites drawn
	*/
	unsigned getSpriteCount() const;

	/**
	 * Starts and activates the batch.
	 */
	void begin();

	/**
	 * Ends and deactivates the batching.
	 * Draws everything not drawn yet.
	 */
	void end();

	/**
	 * Batches, if possible, or otherwise just draws the specified BGO.
	 *
	 * @param bgo        the BGO to batch
	 * @param scenegraph whether to also batch/draw this BGO's children
	 * @param states     the render states to be used for rendering
	 */
	void draw(const BGO &bgo, bool scenegraph = false, sf::RenderStates states = sf::RenderStates::Default);

	/**
	 * Batches the specified SGO.
	 *
	 * @param sgo    the SGO to batch
	 * @param states the render states to be used for rendering
	 */
	void draw(const SGO &sgo, sf::RenderStates states = sf::RenderStates::Default);

	/**
	 * Batches the specified TGO.
	 *
	 * @param tgo    the TGO to batch
	 * @param states the render states to be used for rendering
	 */
	void draw(const TGO &tgo, sf::RenderStates states = sf::RenderStates::Default);

	sf::RenderStates states;

private:
	/**
	 * Prepares the batch for the next intake.
	 *
	 * @param  texture the upcoming texture to be used for the batch
	 * @return         the index of the first vertices to be used for batching
	 */
	unsigned int prepareDraw(const sf::Texture &texture);

	/**
	 * Flushes the current batch.
	 */
	void flush();

	/**
	* Batches the specified vertices of a sprite.
	* The number of vertices in the array must be the same as the value defined by SPRITE_VERTICES.
	*
	* @param texture  the texture to batch with
	* @param vertices the array of vertices
	*/
	void drawSprite(const sf::Texture &texture, const sf::Vertex *vertices);

	sf::RenderTarget &renderer;
	sf::Vertex *vertices;
	unsigned int maxCount, count, cumulativeCount;
	unsigned int count_sprites, count_drawcalls;
	bool active;
};

#endif // BATCH_H