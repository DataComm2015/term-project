
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Event.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--           Jeff Bayntun
--           Eric Tsang
--
-- PROGRAMMER: Marc Rafanan
--             Marc Vouve
--           Jeff Bayntun
--           Eric Tsang
--
-- NOTES:
-- This file defines the Event class members
--
----------------------------------------------------------------------------------------------------------------------*/
#ifndef EVENT_H_
#define EVENT_H_
namespace Marx
{

    /*
     * Event Types
     */
    enum EventType
    {
        MOVE
    };

    /*
     * Event Class
     */
    class Event
    {
    public:
        EventType type;
    };

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
    class MoveEvent: public Event
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
}


#endif /* EVENT_H_ */
