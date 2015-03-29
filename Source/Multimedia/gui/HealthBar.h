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
            HealthBar(const sf::Texture& texture, sf::Vector2f si, sf::View& v);
			void update(float percent);
		private:
			sf::View& view;
			sf::Vector2f size;
	};
}

#endif
