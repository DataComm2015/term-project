#ifndef GUI_CONTAINER
#define GUI_CONTAINER

#include "../graphics/object/BGO.h"
#include "../graphics/object/SGO.h"

namespace GUI
{
	typedef enum orientation{ VERTICAL, HORIZONTAL } orientation;

	class Container : BGO
	{
		public:
			Container(SGO* firstSGO, SGO* secondSGO, sf::Vector2f theSize, orientation theOrientation);
			void setSeperator(SGO* theSeparator);
			void setRatio(float theRatio);
			void setOrientation(orientation theOrientation);
			void setPosition(sf::Vector2f newpos);
			void pack();
			sf::Vector2f getSize();
		private:
			SGO* A;
			SGO* B;
			SGO* separator;
			sf::Vector2f size;
			float ratio;
			orientation orient;
			sf::Vector2f pos;
	};
}

#endif
