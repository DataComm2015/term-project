#ifndef TGO_H
#define TGO_H

#include "BGO.h"

/**
* Text Game Object.
*
* A BGO that represents a text.
*
* @author Melvin Loho
*/
class TGO : public BGO
{
public:
	/**
	* Constructor.
	*/
	TGO();

	/**
	* Destructor.
	*/
	virtual ~TGO();

	/**
	* Returns the text held by this object.
	*/
	sf::Text& operator()();

	/**
	* Returns the text held by this object.
	*/
	const sf::Text& operator()() const;

	/**
	* Gets the local transformation matrix belonging to the
	* text that this BGO is representing.
	*
	* @return the transformation matrix
	*/
	const sf::Transform& getLocalTransform() const override;

	/**
	* Sets the anchor point to one of the following:
	* - the middle of the text.
	* - the top left corner of the text
	*
	* @param arg true/false
	*/
	void middleAnchorPoint(bool arg);

protected:
	/**
	* Draws the text.
	*
	* @param batch  the batcher used to render
	* @param states the render states used to render
	*/
	void draw(Batch& batch, sf::RenderStates states) const override;

private:
	sf::Text data;
};

#endif // TGO_H