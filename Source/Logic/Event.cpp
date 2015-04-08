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

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	setX
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE:	float MoveEvent::setX(float _x)
-- float _x: the x value to set the event with
--
-- RETURNS: 	the x coordinate it has been set to
--
-- NOTES:       Sets the x coordinate of the event, for synchronization across clients.
-----------------------------------------------------------------------------------------------*/
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


 /*----------------------------------------------------------------------------------------------
 -- FUNCTION:	setY
 --
 -- DATE:		April 7, 2015
 --
 -- REVISIONS:	(Date and Description)
 --
 -- DESIGNER:	Sanders Lee
 --
 -- PROGRAMMER:	Sanders Lee
 --
 -- INTERFACE:	float MoveEvent::setY(float _y)
 -- float _y: the y value to set the event with
 --
 -- RETURNS: 	the y coordinate it has been set to
 --
 -- NOTES:      Sets the y coordinate of the event, for synchronization across clients.
 -----------------------------------------------------------------------------------------------*/
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

/* ------------------------------- Skill Event ----------------------------------- */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:	SkillEvent::SkillEvent(float _x, float _y, int _radius, int _value, SKILLTYPE _skillType) :Event(Marx::SKILL)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	SkillEvent::SkillEvent(float _x, float _y, int _radius, int _value, SKILLTYPE _skillType) :Event(Marx::SKILL)
--
-- RETURNS: 	void
--
-- NOTES: 		Constructs a skill event
-----------------------------------------------------------------------------------------------*/
SkillEvent::SkillEvent(float _x, float _y, int _radius, int _value, SKILLTYPE _skillType) :Event(Marx::SKILL)
{
    x = _x;
    y = _y;
    radius = _radius;
    value = _value;
    skillType = _skillType;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	SkillEvent::SkillEvent(const SkillEvent& other):Event(other.type)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	SkillEvent::SkillEvent(const SkillEvent& other):Event(other.type)
--
-- RETURNS: 	void
--
-- NOTES: 		Copys a skill event
-----------------------------------------------------------------------------------------------*/
SkillEvent::SkillEvent(const SkillEvent& other)
    :Event(other.type)
{
    x = other.x;
    y = other.y;
    radius = other.radius;
    value = other.value;
    skillType = other.skillType;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	float SkillEvent::getX()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	float SkillEvent::getX()
--
-- RETURNS: 	x val
--
-- NOTES: 		Gets x val
-----------------------------------------------------------------------------------------------*/
float SkillEvent::getX()
{
    return x;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillEvent::setX(float _x)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	void SkillEvent::setX(float _x)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets x
-----------------------------------------------------------------------------------------------*/
void SkillEvent::setX(float _x)
{
    x = _x;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	float SkillEvent::getY()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	float SkillEvent::getY()
--
-- RETURNS: 	y val
--
-- NOTES: 		Gets y val
-----------------------------------------------------------------------------------------------*/
float SkillEvent::getY()
{
    return y;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillEvent::setY(float _y)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	void SkillEvent::setY(float _y)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets y
-----------------------------------------------------------------------------------------------*/
void SkillEvent::setY(float _y)
{
    y = _y;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	float SkillEvent::getRadius()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	float SkillEvent::getRadius()
--
-- RETURNS: 	radius val
--
-- NOTES: 		Gets radius val
-----------------------------------------------------------------------------------------------*/
float SkillEvent::getRadius()
{
    return radius;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillEvent::setRadius(float _radius)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: void SkillEvent::setRadius(float _radius)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets radius
-----------------------------------------------------------------------------------------------*/
void SkillEvent::setRadius(float _radius)
{
    radius = _radius;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	int SkillEvent::getValue()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	int SkillEvent::getValue()
--
-- RETURNS: 	value val
--
-- NOTES: 		Gets value val
-----------------------------------------------------------------------------------------------*/
int SkillEvent::getValue()
{
    return value;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillEvent::setValue(int _value)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: void SkillEvent::setValue(int _value)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets value
-----------------------------------------------------------------------------------------------*/
void SkillEvent::setValue(int _value)
{
    value = _value;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	SKILLTYPE SkillEvent::getSkillType()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	SKILLTYPE SkillEvent::getSkillType()
--
-- RETURNS: 	skillType val
--
-- NOTES: 		Gets skillType val
-----------------------------------------------------------------------------------------------*/
SKILLTYPE SkillEvent::getSkillType()
{
    return skillType;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillEvent::setSkillType(SKILLTYPE _skillType)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: void SkillEvent::setSkillType(SKILLTYPE _skillType)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets _skillType
-----------------------------------------------------------------------------------------------*/
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


/* ------------------------------- Skill Notification Event ----------------------------------- */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:	SkillNotification::SkillNotification(float _x, float _y, SKILLTYPE _skillType) :Event(Marx::SKILL_NOTIFY)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	SkillNotification::SkillNotification(float _x, float _y, SKILLTYPE _skillType) :Event(Marx::SKILL_NOTIFY)
--
-- RETURNS: 	void
--
-- NOTES: 		Constructs a skill notification event
-----------------------------------------------------------------------------------------------*/
SkillNotification::SkillNotification(float _x, float _y, SKILLTYPE _skillType) :Event(Marx::SKILL_NOTIFY)
{
    x = _x;
    y = _y;
    skillType = _skillType;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	float SkillNotification::getX()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	float SkillNotification::getX()
--
-- RETURNS: 	x val
--
-- NOTES: 		Gets x val
-----------------------------------------------------------------------------------------------*/
float SkillNotification::getX()
{
    return x;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillNotification::setX(float _x)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: void SkillNotification::setX(float _x)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets X
-----------------------------------------------------------------------------------------------*/
void SkillNotification::setX(float _x)
{
    x = _x;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	float SkillNotification::getY()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE:	float SkillNotification::getY()
--
-- RETURNS: 	y val
--
-- NOTES: 		Gets y val
-----------------------------------------------------------------------------------------------*/
float SkillNotification::getY()
{
    return y;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillNotification::setY(float _y)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: void SkillNotification::setY(float _y)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets y
-----------------------------------------------------------------------------------------------*/
void SkillNotification::setY(float _y)
{
    y = _y;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	SKILLTYPE SkillNotification::getSkillType()
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: SKILLTYPE SkillNotification::getSkillType()
--
-- RETURNS: 	skilltype val
--
-- NOTES: 		get skilltype
-----------------------------------------------------------------------------------------------*/
SKILLTYPE SkillNotification::getSkillType()
{
    return skillType;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	void SkillNotification::setSkillType(SKILLTYPE _skillType)
--
-- DATE:		April 3, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Alex Lam, Julian Brandrick
--
-- PROGRAMMER:	Alex Lam, Julian Brandrick
--
-- INTERFACE: void SkillNotification::setSkillType(SKILLTYPE _skillType)
--
-- RETURNS: 	void
--
-- NOTES: 		Sets _skillType
-----------------------------------------------------------------------------------------------*/
void SkillNotification::setSkillType(SKILLTYPE _skillType)
{
    skillType = _skillType;
}
// Ability notification end
