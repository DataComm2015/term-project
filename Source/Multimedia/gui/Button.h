#ifndef BUTTON
#define BUTTON

namespace GUI
{
    //class button extends from sgo
    // so it has everything from sgo and add extra defined here
	class Button : SGO
	{
		public:
            Button(BGO* parent, sf::IntRect* theStates, std::function onClick);
			inline void toggleEnabled(bool enabled);
			void update(sf::Time& t);
		private:
			std::function on_click;
			sf::IntRect[3] states;
            bool toggleEnabled;
	};
}

#endif