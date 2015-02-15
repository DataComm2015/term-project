#ifndef GUI_CONTAINER
#define GUI_CONTAINER

namespace GUI
{
	class Container : BGO
	{
		public:
			Container(BGO*, BGO*, BGO*, sf::Vector2f, bool);
			void setSeperator(SGO*);
			void setRatio(int);
			void setOrientation(bool);
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
