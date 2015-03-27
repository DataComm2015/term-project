#ifndef LOGIC_EVENT_H_
#define LOGIC_EVENT_H_

/*
 * move event message used to send move events over network
 */
struct MoveMessage
{
    float x;
    float y;
    bool forced;
};

/*
 * Move Event Class
 */
class MoveEvent: public ::Marx::Event
{
public:
    MoveEvent(float _x, float _y, bool f=false);
    float getX();
    float getY();
    bool forced();
private:
    float x;
    float y;
    bool force;
};

#endif
