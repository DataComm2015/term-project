#ifndef BUTTON
#define BUTTON

#include <functional>
#include "../graphics/object/SGO.h"

namespace GUI
{
	struct buttonStates
	{
		sf::IntRect disabled;
		sf::IntRect normal;
		sf::IntRect hover;
		sf::IntRect clicked;
	};

    //class button extends from sgo
    // so it has everything from sgo and add extra defined here
	class Button : public SGO
	{
		public:
            Button(BGO* parent, const sf::Texture& texture, const struct buttonStates theStates, std::function<void()> onClick);
			inline void toggleEnabled(bool e);
			void update(sf::Time& t);
		private:
			std::function<void()> on_click;
			struct buttonStates states;
            bool enabled;
	};
}

#endif
