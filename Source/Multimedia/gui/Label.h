#ifndef LABEL
#define LABEL

/*
BGO - Base Game Object
SGO - Sprite Game Object
TGO - Text Game Object
*/


namespace GUI

	class Label : TGO
	{
		public:
			Label(BGO* parent, SGO* theBackground, std::string theText);
			void toggleBackground(bool toggled);
			void setOffset(sf::Vector2f theOffset);
		private:
			SGO* background;
			sf::Vector2f offset;
            bool theBackground;
	};
}

#endif
