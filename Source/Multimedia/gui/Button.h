#ifndef BUTTON
#define BUTTON

#include <functional>
#include "../graphics/object/SGO.h"

namespace GUI
{
    // class button extends from sgo
    // so it has everything from sgo and add extra defined here
	class Button : public SGO
	{
		public:
            Button(const sf::Texture& texture, sf::Vector2f si, sf::View& v, std::function<void()> onClick);
			void toggleEnabled(bool e);
			void update(sf::Time& t);
		private:
			sf::View& view;
			std::function<void()> on_click;
			sf::Vector2f size;
            bool enabled;
            sf::IntRect disabled, normal, hover, clicked;
	};
}

#endif
