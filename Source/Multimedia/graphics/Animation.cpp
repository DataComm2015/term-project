#include "Animation.h"

Animation::Animation(SGO* s, sf::IntRect *frames, short len)
{
	length = len;
	sprite = s;
	position = 0;
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
	increment(by);
	running = false;
	sprite->operator()().setTextureRect(frames[position]);
	
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
		increment();
		sprite->operator()().setTextureRect(frames[position]);
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
