#ifndef VALUE_BUTTON
#define VALUE_BUTTON

namespace GUI
{
	class ValueButton : BGO
	{
		public:
			ValueButton(BGO*, sf::IntRect*, Button*, Button*, Label*, std::function, std::string, int, int);
			~ValueButton();
			void setFormat(int, bool, sf::Color);
			int getValue();
			void setValue(int);
		private:
			Label* label;
			Button* dec, inc;
			int value;
			int mod_by;
			std::function callback;
	};
}

#endif
