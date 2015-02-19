#ifndef LABEL
#define LABEL

namespace GUI
{
	class Label : TGO
	{
		public:
			Label(BGO*, SGO*, std::string);
			void toggleBackground(bool);
			void setOffset(sf::Vector2f);
		private:
			SGO* background;
			sf::Vector2f offset;
	};
}

#endif
