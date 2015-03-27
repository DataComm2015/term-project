#include "Animation.h"

/**
 * Animation.
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @notes      Modifies the sub-rects of a sprite to display an animation
 */

/**
 * Constructor.
 *
 * @param: SGO* s: The SGO that contains the sprite to update
 * @param: sf::Vector2i: si: The size of a frame
 * @param: short len: The number of frames
 * @param: short sk: The number of frames to skip before advancing a frame in the animation
 */
Animation::Animation(SGO* s, sf::Vector2i si, short len, short sk)
{
	length = len;
	sprite = s;
	position = steps = 0;
	size = si;
	skip = sk;
	running = loop = false;
}

/*
* Destructor.
*/
Animation::~Animation()
{}

/**
 * Runs the animation
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @param	   bool: l: Whether to loop
 *
 * @return     void
 */
void Animation::run(bool l)
{
	loop = l;
	running = true;
}

/**
 * Pauses/stops the animation
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @param	   bool: stop: Whether reset the animation to the beginning
 *
 * @return     void
 */
void Animation::pause(bool stop)
{
	running = false;
	
	if(stop)
		position = 0;
}

/**
 * Runs an animation from the beginning
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @param	   bool: l: Whether to loop
 *
 * @return     void
 */
void Animation::restart(bool l)
{
	position = 0;
	running = true;
	loop = l;
}

/**
 * Increments by a given number of frames
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @param	   short: by: The number of frames to advance by
 *
 * @return     short: The current frame position
 */
short Animation::step(short by)
{
	if(steps >= skip)
	{
		increment(by);
		sprite->sprite().setTextureRect(sf::IntRect((size.x * position), 0, size.x, size.y));
		steps = 0;
	}
	else
		steps++;
	
	return position;
}

/**
 * Gets whether or not the animation is currently running.
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @return     bool: Whether the animation is running
 */
bool Animation::isRunning()
{
	return running;
}

/**
 * Gets whether or not the animation is looping.
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @return     bool: Whether the animation is looping
 */
bool Animation::isLooping()
{
	return loop;
}

/**
 * 1-Frame update for the animation, must be called each tick to run properly.
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @param	   sf::Time&: t: The current time; Currently unused
 *
 * @return     void
 */
void Animation::update(sf::Time& t)
{
	if(running)
	{
		step();
	}
}

void Animation::setFrameSkip(short i)
{
	skip = i;
}

/**
 * Increments the animation by the given number of frames
 *
 * @date       2015-03-16
 *
 * @revisions
 *
 * @designer   Lewis Scott
 *
 * @programmer Lewis Scott
 *
 * @param	   short: by: The number of frames to increment by
 *
 * @return     void
 */
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
