#ifndef SGO_H
#define SGO_H

#include "BGO.h"

/**
 * Sprite Game Object.
 * 
 * A BGO that represents a sprite.
 * 
 * @author Melvin Loho
 */
class SGO : public BGO
{
public:
	/**
	 * Constructor.
	 */
	SGO();

	/**
	 * Constructor.
	 *
	 * @param texture the texture to assign to the sprite
	 */
	SGO(const sf::Texture &texture);

	/**
	 * Constructor.
	 *
	 * @param texture the texture to assign to the sprite
	 * @param rect    the sub rect of the texture that the sprite should display
	 */
	SGO(const sf::Texture &texture, const sf::IntRect &rect);

	/**
	 * Destructor.
	 */
	virtual ~SGO();

	/**
	 * Returns the sprite held by this object.
	 */
	sf::Sprite& operator()();

	/**
	 * Returns the sprite held by this object.
	 */
	const sf::Sprite& operator()() const;

	/**
	 * Gets the local transformation matrix belonging to the
	 * sprite that this BGO is representing.
	 *
	 * @return the transformation matrix
	 */
	const sf::Transform &getLocalTransform() const override;

	/**
	 * Draws the sprite.
	 *
	 * @param batch  the batcher used to render
	 * @param states the render states used to render
	 */
	void draw(ObjectBatch &batch, sf::RenderStates states) const override;

	/**
	 * Sets the anchor point to one of the following:
	 * - the middle of the sprite.
	 * - the top left corner of the sprite
	 *
	 * @param arg true/false
	 */
	void middleAnchorPoint(bool arg);

private:
	sf::Sprite data;
};

#endif // SGO_H