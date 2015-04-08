
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
--             Thomas Tallentire
--			   Julian Brandrick
--
-- NOTES:
-- This file defines the Event class members
--
----------------------------------------------------------------------------------------------------------------------*/
#ifndef EVENT_H_
#define EVENT_H_

enum ActionType
{
	normalAttack = 0x11, specialAttack
};

namespace Marx
{

    /*
     * Event Types
     */
    enum EventType
    {
        MOVE,
      	R_MOVE,
        A_MOVE,
        ATTACK,
        SK_ATTACK,
        UPDATE,
        SET_HEALTH,
        SKILL,
		SKILL_NOTIFY,
		ADD_POINTS
    };

    /*
     * Event Class
     */
    class Event
    {
    public:
        Event(EventType e):type(e) {};
        Event(const Event& other):type(other.type) {};
        const EventType type;
    };
}


#endif /* EVENT_H_ */
