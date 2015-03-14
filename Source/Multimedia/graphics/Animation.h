#include "object/SGO.h"

class Animation
{
	public:
		Animation(SGO*, sf::IntRect*, short, short = 0);
		virtual ~Animation();
		void run(bool = false);
		void pause(bool = false);
		void restart(bool = false);
		short step(short = 1);
		bool isRunning();
		bool isLooping();
		void update(sf::Time& t);
	private:
		void increment(short = false);
	
		SGO* sprite;
		sf::IntRect *frames;
		short position, length, skip;
		bool running, loop;
};
