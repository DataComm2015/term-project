/*----------------------------------------------------------------------------------------------
-- FILE:        	Event.cpp
--
-- DATE:			April 1, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Jeff Bayntun
--
-- PROGRAMMER:		Jeff Bayntun, Sanders Lee
--
-- INTERFACE:		MoveEvent(float _x, float _y, int _xDir, int _yDir, bool f=false);
                    MoveEvent(MoveEvent&& other);
                    MoveEvent(const MoveEvent& other);
                    float getX();
                    float setX(float _x);
                    float getY();
                    float setY(float _y);
                    int getXDir();
                    int getYDir();
                    bool forced();


-- NOTES:			These are events that can be send to entities for things like moving and
                    attacking.
-----------------------------------------------------------------------------------------------*/
#include "Event.h"

#include "../Engine/Event.h"

/* ------------------------------- Move Event ----------------------------------- */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:	MoveEvent
--
-- DATE:		April 1, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Jeff Bayntun
--
-- PROGRAMMER:	Jeff Bayntun
--
-- INTERFACE:	MoveEvent::MoveEvent(float _x, float _y, int _xDir, int _yDir, bool f)
--
-- RETURNS: 	void
--
-- NOTES: 		constructs a move event.
-----------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	getX
--
-- DATE:		April 1, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Jeff Bayntun
--
-- PROGRAMMER:	Jeff Bayntun
--
-- INTERFACE:	float getX()
--
-- RETURNS: 	X value to move to
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	getY
--
-- DATE:		April 1, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Jeff Bayntun
--
-- PROGRAMMER:	Jeff Bayntun
--
-- INTERFACE:	float getY()
--
-- RETURNS: 	Y value to move to
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	forced
--
-- DATE:		April 1, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Jeff Bayntun
--
-- PROGRAMMER:	Jeff Bayntun
--
-- INTERFACE:	bool forced()
--
-- RETURNS: 	true if the move is forced
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
bool MoveEvent::forced()
{
    return force;
}

// Ability event start 
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
// Ability event end 

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
SetHealthEvent::SetHealthEvent(int id, bool _type, float _change) : entid(id), typeHeal(_type), change(_change), Event(Marx::SET_HEALTH)
{
}

int SetHealthEvent::getEntId()
{
	return entid;
}

bool SetHealthEvent::getTypeHeal()
{
	return type;
}

float SetHealthEvent::getChange()
{
    return change;
}


/* ------------------------------- Add Points Event ------------------------------------*/
AddPointsEvent::AddPointsEvent(float _points) : points(_points), Event(Marx::ADD_POINTS)
{
}

float AddPointsEvent::getPoints()
{
	return points;
}


// Ability notification start 
SkillNotification::SkillNotification(float _x, float _y, SKILLTYPE _skillType) :Event(Marx::SKILL_NOTIFY)
{
    x = _x;
    y = _y;
    skillType = _skillType;
}

float SkillNotification::getX()
{
    return x;
}

void SkillNotification::setX(float _x)
{
    x = _x;
}

float SkillNotification::getY()
{
    return y;
}

void SkillNotification::setY(float _y)
{
    y = _y;
}

SKILLTYPE SkillNotification::getSkillType()
{
    return skillType;
}

void SkillNotification::setSkillType(SKILLTYPE _skillType)
{
    skillType = _skillType;
}
// Ability notification end 

