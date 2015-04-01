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
    float getY();
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
  UpdateEvent() : Event(Marx::UPDATE){}
};

#endif
