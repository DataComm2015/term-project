
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
}


#endif /* EVENT_H_ */
