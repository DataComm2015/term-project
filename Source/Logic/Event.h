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

class UpdateEvent: public ::Marx::Event
{
public:
  UpdateEvent(float x, float y) : Event(Marx::UPDATE), _x(x), _y(y){}
  float _x;
  float _y;

};

class SkillEvent: public ::Marx::Event
{
    public:
        SkillEvent(float _x, float _y, float _radius, int _value, int _skillType);
        SkillEvent(const SkillEvent& other);
        float getX();
        void setX(float _x);
        float getY();
        void setY(float _y);
        float getRadius();
        void setRadius(float _radius);
        int getValue();
        void setValue(int _value);
        int getSkillType();
        void setSkillType(int _skillType);
        
    private:
        float x;
        float y;
        float radius;
        int value;
        int skillType;
};

#endif
