#ifndef LOGIC_EVENT_H_
#define LOGIC_EVENT_H_

#include "../Engine/Event.h"
#include "Skills.h"

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
	bool typeHeal;
	float change;
};

class SetHealthEvent : public ::Marx::Event
{
public:
	SetHealthEvent(int id, bool _type, float _change);
	int getEntId();
	bool getTypeHeal();
	float getChange();
private:
	int entid;
	bool typeHeal;
	float change;
};

class SkillEvent: public ::Marx::Event
{
    public:
        SkillEvent(float _x, float _y, int _radius, int _value, SKILLTYPE _skillType);
        SkillEvent(const SkillEvent& other);
        float getX();
        void setX(float _x);
        float getY();
        void setY(float _y);
        float getRadius();
        void setRadius(float _radius);
        int getValue();
        void setValue(int _value);
        SKILLTYPE getSkillType();
        void setSkillType(SKILLTYPE _skillType);

    private:
        float x;
        float y;
        float radius;
        int value;
        SKILLTYPE skillType;
};

class SkillNotification: public ::Marx::Event
{
    public:
        SkillNotification(float _x, float _y, SKILLTYPE _skillType);
        float getX();
        void setX(float _x);
        float getY();
        void setY(float _y);
        SKILLTYPE getSkillType();
        void setSkillType(SKILLTYPE _skillType);

    private:
        float x;
        float y;
        SKILLTYPE skillType;
};

struct AddPointsMessage
{
	float points;
};

class AddPointsEvent : public ::Marx::Event
{
public:
	AddPointsEvent(float);
	float getPoints();
private:
	float points;
};


#endif
