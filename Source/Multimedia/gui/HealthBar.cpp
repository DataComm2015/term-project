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
	HealthBar::HealthBar(const sf::Texture& bgtexture, const sf::Texture& bartexture, sf::Vector2f si, sf::View& v) : SGO(bgtexture), view(v)
	{
		bgSize = si;
		sprite().setTextureRect(sf::IntRect(0, 0, bgSize.x, bgSize.y));

		// Create the bar
		bar = SGO(bartexture);
		barSize = bartexture.getSize();

		bar.sprite().setTextureRect(sf::IntRect(0, 0, barSize.x, barSize.y));
        bar.sprite().setPosition(5, 0);

		this->add(bar);
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
		//bar.sprite().setTextureRect(sf::IntRect(0, 0, barSize.x - (barSize.x * (1.0 - percent)), barSize.y));
	}
}
