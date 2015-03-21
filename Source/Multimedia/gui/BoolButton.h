#ifndef BOOLBUTTON
#define BOOLBUTTON

namespace GUI
{
	class BoolButton : Button
	{
		public:
			BoolButton(sf::IntRect* theStates, std::function onClick, SGO* toCheck, bool theState);
			bool getState();
			void update(sf::Time& t);
		private:
			bool state;
			SGO* check;
	};
}

#endif
