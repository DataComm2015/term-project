#ifndef GUI_CONTAINER
#define GUI_CONTAINER

namespace GUI
{
	class Container : BGO
	{
		public:
			Container(BGO* parent, BGO* firstBGO, BGO* secondBGO, sf::Vector2f theScale, bool theOrientation);
			void setSeperator(SGO* theSeparator);
			void setRatio(int theRatio);
			void setOrientation(bool theOrientation);
			void pack();
		private:
			BGO* A, B;
			SGO* seperator;
			sf::Vector2f scale;
			int ratio;
			bool orientation;
	};
}

#endif