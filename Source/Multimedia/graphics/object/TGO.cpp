/**
 * Text Game Object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @notes      A BGO that represents a text.
 */

#include "TGO.h"

#include "../Renderer.h"

/**
 * Constructor.
 */
TGO::TGO()
{}

/**
 * Destructor.
 */
TGO::~TGO()
{}

/**
 * Returns the text represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The text
 */
sf::Text& TGO::operator()()
{
	return data;
}

/**
 * Returns the text represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions  
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The text (const-qualified)
 */
const sf::Text& TGO::operator()() const
{
	return data;
}

/**
 * Gets the local transformation matrix belonging to the text represented by this game object.
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
const sf::Transform& TGO::getLocalTransform() const
{
	return data.getTransform();
}

/**
 * Sets the anchor point to one of the following:
 * > the middle of the text
 * > the top left corner of the text
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
void TGO::middleAnchorPoint(bool arg)
{
	if (arg)
	{
		const sf::FloatRect &bounds = data.getLocalBounds();
		data.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	}
	else data.setOrigin(0.f, 0.f);
}

/**
 * Draws the text represented by this game object.
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
void TGO::draw(Renderer& renderer, sf::RenderStates states) const
{
	renderer.draw(*this, states);
}
