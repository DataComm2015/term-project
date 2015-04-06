#ifndef LOGIC_EVENT_H_
#define LOGIC_EVENT_H_

#include "../Engine/Event.h"

/*
 * move event message used to send move events over network
 */
struct MoveMessage
{
    float x;
    float y;
    int xDir;
    int yDir;
    bool forced;
};

struct UpdateMessage
{
  float x;
  float y;
};

/*
 * Move Event Class
 */
class MoveEvent: public ::Marx::Event
{
public:
    MoveEvent(float _x, float _y, int _xDir, int _yDir, bool f=false);
    MoveEvent(MoveEvent&& other);
    MoveEvent(const MoveEvent& other);
    float getX();
    float setX(float _x);
    float getY();
    float setY(float _y);
    int getXDir();
    int getYDir();
    bool forced();
private:
    float x;
    float y;
    int xDir;
    int yDir;
    bool force;
};

struct AttackMessage
{
	int srcid; // Entity id source
    float srcx;
    float srcy;
	enum ActionType action; // Type of attack to take
	int cellx; // Coordinates of the cell you're attacking.
	int celly;
};

class UpdateEvent: public ::Marx::Event
{
public:
  	UpdateEvent(float x, float y) : Event(Marx::UPDATE), _x(x), _y(y){}
  float _x;
  float _y;
};

class AttackEvent : public ::Marx::Event
{
public:
	AttackEvent(int _srcid, enum ActionType type, int _cellx, int _celly);
	int getSrc();
	enum ActionType getAction();
	int getCellX();
	int getCellY();
private:
	int srcid;
	enum ActionType action;
	int cellx;
	int celly;
};

struct SkillAttackMessage
{
	int srcid; // Entity id source
	enum ActionType action; // Type of attack to take
	float destx;
	float desty;
};

class SkillAttackEvent : public ::Marx::Event
{
public:
	SkillAttackEvent(int _srcid, enum ActionType type, int _destx, int _desty);
	int getSrc();
	enum ActionType getAction();
	int getDestX();
	int getDestY();
private:
	int srcid;
	enum ActionType action;
	int destx;
	int desty;
};

struct SetHealthMessage
{
	int entid; // Entity id source
	float change;
};

class SetHealthEvent : public ::Marx::Event
{
public:
	SetHealthEvent(float _change);
	float getChange();
private:
	float change;
};

#endif
