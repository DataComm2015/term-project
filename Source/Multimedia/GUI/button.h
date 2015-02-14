#ifndef BUTTON
#define BUTTON

namespace GUI
{
	class Button : SGO
	{
		public:
			Button(BGO*, sf::IntRect*, std::function);
			void toggleEnabled(bool);
			void update(sf::Time&);
		private:
			std::function on_click;
			sf::IntRect[3] states;
	};
}

#endif
