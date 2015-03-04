#ifndef BOOLBUTTON
#define BOOLBUTTON

namespace GUI
{
	class BoolButton : Button
	{
		public:
			BoolButton(BGO*, sf::IntRect*, std::function, SGO*, bool);
			bool getState();
			void update(sf::Time&);
		private:
			bool state;
			SGO* check;
	};
}

#endif
