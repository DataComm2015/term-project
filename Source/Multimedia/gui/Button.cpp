#include "Button.h"

namespace GUI
{
	/**
	* Initializes a button with the states and the function when clicked.
	*
	* @date         2015-02-27
	*
	* @revisions
	*
	* @designer   
	*
	* @programmer   Jonathan Chu
	*				Lewis Scott
	*
	* @return       initializer
	*/
	Button::Button(BGO* parent, const sf::Texture& texture, const struct buttonStates theStates, std::function<void()> onClick) : SGO(texture)
	{
		parent->add(*this);
		enabled = true;
		states = theStates;
		on_click = onClick;
		SGO::operator()().setTextureRect(states.normal);
	}

	/**
	* Enables the toggling of the button based on the 'enabled' given
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
	inline void Button::toggleEnabled(bool e)
	{
		enabled = e;
	}

	/**
	* Updates the button
	*
	* @date         2015-02-27
	*
	* @revisions
	*
	* @designer     
	*
	* @programmer   Jonathan Chu
	*				Lewis Scott
	*
	* @return       void   
	*/
	void Button::update(sf::Time& t)
	{
		static bool tog = false;

		if(enabled) // button enabled
		{
			if(SGO::operator()().getLocalBounds().contains((sf::Vector2f)sf::Mouse::getPosition())) // mouse inside button
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) // mouse clicking button
				{
					SGO::operator()().setTextureRect(states.clicked);
					
					// So that holding the mouse doesn't activate multiple times
					if(!tog)
					{
						on_click();
						tog = true;
					}
				}
				else // mouse just hovering
					SGO::operator()().setTextureRect(states.hover);
			}
			else //mouse outside button
				SGO::operator()().setTextureRect(states.normal);
		}
		else // button disabled
			SGO::operator()().setTextureRect(states.disabled);
			
		// Reset the button if the mouse is released
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			tog = false;
	}
}
