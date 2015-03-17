#include "Button.h"

#include "../../AppWindow.h"

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
	Button::Button(BGO* parent, const sf::Texture& texture, sf::Vector2f si, std::function<void()> onClick) : SGO(texture)
	{
		parent->add(*this);
		enabled = true;
		tog = false;
		size = si;
		on_click = onClick;
		hover_on = NULL;
		hover_off = NULL;
		disabled = sf::IntRect(0, 0, size.x, size.y);
		normal = sf::IntRect(size.x, 0, size.x, size.y);
		hover = sf::IntRect(size.x * 2, 0, size.x, size.y);
		clicked = sf::IntRect(size.x * 3, 0, size.x, size.y);
		SGO::operator()().setTextureRect(normal);
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
	void Button::toggleEnabled(bool e)
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
		if(enabled) // button enabled
		{
			if(SGO::operator()().getLocalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(AppWindow::getInstance()))) // mouse inside button
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) // mouse clicking button
				{
					SGO::operator()().setTextureRect(clicked);
					
					// So that holding the mouse doesn't activate multiple times
					if(!tog)
					{
						on_click();
						tog = true;
					}
				}
				else // mouse just hovering
				{
					SGO::operator()().setTextureRect(hover);
				}
				
				if(hover_on != NULL)
					hover_on();
			}
			else //mouse outside button
			{
				SGO::operator()().setTextureRect(normal);
				if(hover_off != NULL)
					hover_off();
			}
		}
		else // button disabled
			SGO::operator()().setTextureRect(disabled);
			
		// Reset the button if the mouse is released
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			tog = false;
	}
	
	void Button::setHoverCallbacks(std::function<void()> on, std::function<void()> off)
	{
		hover_on = on;
		hover_off = off;
	}
}
