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
 * Sets the x coordinate, for synchronization across clients.
 * DESIGNER:    Sanders Lee
 * PROGRAMMER:  Sanders Lee
 * @return    the x coordinate it has been set to
 */
float MoveEvent::setX(float _x)
{
    x = _x;
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

/**
 * Sets the y coordinate, for synchronization across clients.
 * DESIGNER:    Sanders Lee
 * PROGRAMMER:  Sanders Lee
 * @return    the y coordinate it has been set to
 */
float MoveEvent::setY(float _y)
{
    y = _y;
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


SkillEvent::SkillEvent(float _x, float _y, int _radius, int _value, int _skillType) :Event(Marx::SKILL)
{
    x = _x;
    y = _y;
    radius = _radius;
    value = _value;
    skillType = _skillType;
}

SkillEvent::SkillEvent(const SkillEvent& other)
    :Event(other.type)
{
    x = other.x;
    y = other.y;
    radius = other.radius;
    value = other.value;
    force = other.force;
}

float SkillEvent::getX()
{
    return x;
}

float SkillEvent::setX(float _x)
{
    x = _x;
    return x;
}

float SkillEvent::getY()
{
    return y;
}

float SkillEvent::setY(float _y)
{
    y = _y;
    return y;
}

float SkillEvent::getRadius()
{
    return radius;
}

void SkillEvent::setRadius(float _radius)
{
    radius = _radius;
}

int SkillEvent::getValue()
{
    return value;
}

void SkillEvent::setValue(int _value)
{
    value = _value;
}

int SkillEvent::getSkillType()
{
    return skillType;
}

void SkillEvent::setSkillType(int _skillType)
{
    skillType = _skillType;
}