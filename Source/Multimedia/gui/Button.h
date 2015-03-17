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
            Button(BGO* parent, const sf::Texture& texture, sf::Vector2f si, std::function<void()> onClick);
			void toggleEnabled(bool e);
			void update(sf::Time& t);
			void setHoverCallbacks(std::function<void()> on, std::function<void()> off);
		private:
			std::function<void()> on_click, hover_on, hover_off;
			sf::Vector2f size;
            bool enabled, tog;
            sf::IntRect disabled, normal, hover, clicked;
	};
}

#endif
