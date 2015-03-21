#ifndef ANIMATION_H
#define ANIMATION_H

#include "object/SGO.h"

class Animation
{
	public:
		Animation(SGO*, sf::Vector2i, short, short = 0);
		virtual ~Animation();
		void run(bool = false);
		void pause(bool = false);
		void restart(bool = false);
		short step(short = 1);
		bool isRunning();
		bool isLooping();
		void update(sf::Time& t);
		void setFrameSkip(short i);
	private:
		void increment(short = false);
	
		SGO* sprite;
		sf::Vector2i size;
		short position, length, skip, steps;
		bool running, loop;
};

#endif
