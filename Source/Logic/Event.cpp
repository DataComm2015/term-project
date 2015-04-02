#include "Event.h"

#include "../Engine/Event.h"

/**
 * constructs a new move event
 *
 * @param _x new n position the entity should move to
 * @param _y new y position that the entity should move to
 * @param f whatever forced means
 */
MoveEvent::MoveEvent(float _x, float _y, int _xDir, int _yDir, bool f)
    :Event(Marx::MOVE)
{
    x = _x;
    y = _y;
    xDir = _xDir;
    yDir = _yDir;
    force = f;
}

MoveEvent::MoveEvent(const MoveEvent& other)
    :Event(other.type)
{
    x = other.x;
    y = other.y;
    xDir = other.xDir;
    yDir = other.yDir;
    force = other.force;
}

/**
 * returns the x property of the move event.
 *
 * @return   x property of the move event.
 */
float MoveEvent::getX()
{
    return x;
}

/**
 * returns the y property of the move event.
 *
 * @return   y property of the move event.
 */
float MoveEvent::getY()
{
    return y;
}

int MoveEvent::getXDir()
{
    return xDir;
}

int MoveEvent::getYDir()
{
    return yDir;
}

/**
 * returns the force property of the move event.
 *
 * @return   force property of the move event.
 */
bool MoveEvent::forced()
{
    return force;
}
