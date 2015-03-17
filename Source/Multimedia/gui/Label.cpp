
#include "Label.h"

namespace GUI
{
	/**
	* Initializes a label
	*
	* @date         2015-02-27
	*
	* @revisions
	*
	* @designer   
	*
	* @programmer   Jonathan Chu
	*
	* @return       initializer
	*/
	Label::Label(BGO* parent, SGO* theBackground, std::string theText)
	{
		parent->add(*this);
		back_enabled = true;
		background = theBackground;
		add(*background);
		
		TGO::operator()().setString(theText);
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
		background->operator()().move(offset);
	}
	
	void Label::setText(std::string text)
	{
		TGO::operator()().setString(text);
	}
}
