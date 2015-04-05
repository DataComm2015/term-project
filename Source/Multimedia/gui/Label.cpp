
#include "Label.h"

namespace GUI
{
	/**
	* Initializes a label
	*
	* @date         2015-02-27
	*
	* @revisions	2015-03-18 - Removed BGO parent from constructor
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*				Marc Rafanan
	*
	* @return       initializer
	*/
	Label::Label(SGO* theBackground, std::string theText)
	{
		back_enabled = true;

		text().setString(theText);
	}

	/**
	* Toggles the background between on/off
	*
	* @date         2015-02-27
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*
	* @return       void
	*/
	void Label::toggleBackground(bool toggled)
	{
		back_enabled = toggled;
	}

	/**
	* Sets the offset based on the offset given
	*
	* @date         2015-02-27
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*
	* @return       void
	*/
	void Label::setOffset(sf::Vector2f theOffset)
	{
		offset = theOffset;
		background->sprite().move(offset);
	}

	void Label::setText(std::string text)
	{
		this->text().setString(text);
	}
}
