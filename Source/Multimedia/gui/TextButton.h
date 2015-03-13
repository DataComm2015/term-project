#ifndef TEXT_BUTTON
#define TEXT_BUTTON

namespace GUI
{
	class TextButton : Button
	{
		public:
			TextButton(BGO*, sf::IntRect*, std::function, std::string);
			~TextButton();
			void setText(std::string);
			void setOffset(sf::Vector2f);
			void setFormat(int, bool, sf::Color);
		private:
			TGO* text;
			sf::Vector2f offset;
	};
}

#endif