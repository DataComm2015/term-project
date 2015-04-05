#ifndef LABEL
#define LABEL

#include "../graphics/object/TGO.h"
#include "../graphics/object/SGO.h"


namespace GUI
{
	class Label : public TGO
	{
		public:
			Label(SGO* theBackground, std::string theText);
			void toggleBackground(bool toggled);
			void setOffset(sf::Vector2f theOffset);
			void setText(std::string text);
		private:
			SGO* background;
			sf::Vector2f offset;
            bool back_enabled;
	};
}

#endif
