#include "HealthBar.h"

#include "../../AppWindow.h"

namespace GUI
{
	/**
	* Initializes the health bar object
	*
	* @date         2015-03-29
	*
	* @revisions	
	*
	* @designer		Marc Rafanan
	*
	* @programmer   Marc Rafanan
	*
	* @return       initializer
	*/
	HealthBar::HealthBar(const sf::Texture& texture, sf::Vector2f si, sf::View& v) : SGO(texture), view(v)
	{
		size = si;
		sprite().setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	}

	/**
	* Updates the health bar
	*
	* @date         2015-03-29
	*
	* @revisions
	*
	* @designer		Marc Rafanan
	*
	* @programmer   Marc Rafanan
	*
	* @return       void
	*/
	void HealthBar::update(float percent)
	{
		sprite().setTextureRect(sf::IntRect(0, 0, size.x - (size.x*(1.0 - percent)), size.y));
	}
}
