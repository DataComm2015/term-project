/**
 * Sprite Game Object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @notes      A BGO that represents a sprite.
 */

#include "SGO.h"

#include "../Renderer.h"

/**
 * Constructor.
 */
SGO::SGO()
{}

/**
 * Constructor.
 * Also sets the texture of the sprite.
 */
SGO::SGO(const sf::Texture& texture)
{
	data.setTexture(texture);
}

/**
 * Constructor.
 * Also sets the texture of the sprite and the sub rectangle that the sprite should display.
 */
SGO::SGO(const sf::Texture& texture, const sf::IntRect& rect)
{
	data.setTexture(texture);
	data.setTextureRect(rect);
}

/**
 * Destructor.
 */
SGO::~SGO()
{}

/**
 * Returns the sprite represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The sprite
 */
sf::Sprite& SGO::operator()()
{
	return data;
}

/**
 * Returns the sprite represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The sprite (const-qualified)
 */
const sf::Sprite& SGO::operator()() const
{
	return data;
}

/**
 * Gets the local transformation matrix belonging to the sprite represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The transformation matrix
 */
const sf::Transform& SGO::getLocalTransform() const
{
	return data.getTransform();
}

/**
 * Sets the anchor point to one of the following:
 * > the middle of the sprite
 * > the top left corner of the sprite
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      arg True/False
 */
void SGO::middleAnchorPoint(bool arg)
{
	if (arg)
	{
		const sf::FloatRect &bounds = data.getLocalBounds();
		data.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	}
	else data.setOrigin(0.f, 0.f);
}

/**
 * Draws the sprite represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      renderer The renderer
 * @param      states   The render states
 */
void SGO::draw(Renderer& renderer, sf::RenderStates states) const
{
	renderer.draw(*this, states);
}