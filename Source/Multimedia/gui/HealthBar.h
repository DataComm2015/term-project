#ifndef HEALTHBAR
#define HEALTHBAR

#include <functional>
#include "../graphics/object/SGO.h"

namespace GUI
{
    // class healthbar extends from sgo
    // so it has everything from sgo and add extra defined here
	class HealthBar : public SGO
	{
		public:
            HealthBar(const sf::Texture& bgtexture, const sf::Texture& bartexture, sf::Vector2f si, sf::View& v);
			void update(float percent);
		private:
			sf::View& view;
			sf::Vector2f bgSize;
			sf::Vector2u barSize;
			SGO bar;
	};
}

#endif
