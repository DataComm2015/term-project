#ifndef VALUE_BUTTON
#define VALUE_BUTTON

namespace GUI
{
    //should bgo be button instead?
	class ValueButton : BGO
	{
		public:
			ValueButton(BGO* parent, sf::IntRect* decButton, Button* incButton, Button*, Label* theLabel, std::function theFunc, std::string theText, int theValue, int modBy);
			~ValueButton();
			void setFormat(int, bool, sf::Color);
			int getValue();
			void setValue(int requiredValue);
		private:
			Label* label;
			Button* dec, inc;
			int value;
			int mod_by;
			std::function callback;
	};
}

#endif