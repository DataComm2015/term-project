#include "Animation.h"

Animation::Animation(SGO* s, sf::IntRect *f, short len, short sk)
{
	length = len;
	sprite = s;
	position = 0;
	frames = f;
	skip = sk;
	running = loop = false;
}

Animation::~Animation()
{}

void Animation::run(bool l)
{
	loop = l;
	running = true;
}

void Animation::pause(bool stop)
{
	running = false;
	
	if(stop)
		position = 0;
}

void Animation::restart(bool l)
{
	position = 0;
	running = true;
	loop = l;
}

short Animation::step(short by)
{
	static short i = 0;
	
	if(i >= skip)
	{
		increment(by);
		sprite->operator()().setTextureRect(frames[position]);
		i = 0;
	}
	else
		i++;
	
	return position;
}

bool Animation::isRunning()
{
	return running;
}

bool Animation::isLooping()
{
	return loop;
}

void Animation::update(sf::Time& t)
{
	if(running)
	{
		step();
	}
}

void Animation::increment(short by)
{
	position += by;

	if(position >= length)
	{
		position -= length;
		if(!loop)
			running = false;
	}
}
