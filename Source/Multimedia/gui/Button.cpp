#include "Button.h"

#include "../../AppWindow.h"

namespace GUI
{
	/**
	* Initializes a button with the states and the function when clicked.
	*
	* @date         2015-02-27
	*
	* @revisions	2015-03-18 - Removed BGO parent from constructor
	*
	* @designer   
	*
	* @programmer   Jonathan Chu
	*				Lewis Scott
	*				Marc Rafanan
	*
	* @return       initializer
	*/
	Button::Button(const sf::Texture& texture, sf::Vector2f si, sf::View& v, std::function<void()> onClick) : SGO(texture), view(v)
	{
		enabled = true;
		size = si;
		on_click = onClick;
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
		static bool tog = false;
		static AppWindow& appWindow = AppWindow::getInstance();

		if(enabled) // button enabled
		{
			if(SGO::operator()().getLocalBounds().contains(appWindow.getMousePositionRelativeToWindowAndView(view))) // mouse inside button
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
					SGO::operator()().setTextureRect(hover);
			}
			else //mouse outside button
				SGO::operator()().setTextureRect(normal);
		}
		else // button disabled
			SGO::operator()().setTextureRect(disabled);
			
		// Reset the button if the mouse is released
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			tog = false;
	}
}
