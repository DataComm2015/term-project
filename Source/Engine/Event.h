
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
-- DESIGNER:   Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--             Marc Vouve
--             Jeff Bayntun
--             Eric Tsang
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
        MOVE,
	R_MOVE,
	A_MOVE
    };

    /*
     * Event Class
     */
    class Event
    {
    public:
        Event(EventType e):type(e) {};
        const EventType type;
    };
}


#endif /* EVENT_H_ */
