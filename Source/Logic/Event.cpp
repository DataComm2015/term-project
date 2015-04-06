#include "Event.h"

#include "../Engine/Event.h"

/* ------------------------------- Move Event ----------------------------------- */
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

// Ability event start \\
SkillEvent::SkillEvent(float _x, float _y, int _radius, int _value, SKILLTYPE _skillType) :Event(Marx::SKILL)
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
    skillType = other.skillType;
}

float SkillEvent::getX()
{
    return x;
}

void SkillEvent::setX(float _x)
{
    x = _x;
}

float SkillEvent::getY()
{
    return y;
}

void SkillEvent::setY(float _y)
{
    y = _y;
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

SKILLTYPE SkillEvent::getSkillType()
{
    return skillType;
}

void SkillEvent::setSkillType(SKILLTYPE _skillType)
{
    skillType = _skillType;
}
// Ability event end \\

/* ------------------------------- Attack Event ----------------------------------- */
AttackEvent::AttackEvent(int _srcid, enum ActionType type, int _cellx, int _celly) :
	Event(Marx::ATTACK), srcid(_srcid), action(type), cellx(_cellx), celly(_celly)
{
}

int AttackEvent::getSrc()
{
	return srcid;
}

enum ActionType AttackEvent::getAction()
{
	return action;
}

int AttackEvent::getCellX()
{
	return cellx;
}

int AttackEvent::getCellY()
{
	return celly;
}


/* ------------------------------- Skill Attack Event ----------------------------------- */
SkillAttackEvent::SkillAttackEvent(int _srcid, enum ActionType type, int _destx, int _desty) :
	Event(Marx::SK_ATTACK), srcid(_srcid), action(type), destx(_destx), desty(_desty)
{
}

int SkillAttackEvent::getSrc()
{
	return srcid;
}

enum ActionType SkillAttackEvent::getAction()
{
	return action;
}

int SkillAttackEvent::getDestX()
{
	return destx;
}

int SkillAttackEvent::getDestY()
{
	return desty;
}

/* ------------------------------- Set Health Event ------------------------------------*/
SetHealthEvent::SetHealthEvent(float _change) : change(_change), Event(Marx::SET_HEALTH)
{
}

float SetHealthEvent::getChange()
{
    return change;
}

