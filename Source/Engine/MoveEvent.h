#include "Event.h"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: MoveEvent.h
-- 
-- PROGRAM:
-- 
-- FUNCTIONS: N/A
-- 
-- DATE: March 20, 2015
-- 
-- REVISIONS:
-- 
-- DESIGNER: Jeff Bayntun
-- 
-- PROGRAMMER: Jeff Bayntun
-- 
-- NOTES:
-- This file defines the MoveEvent class members
-- 
----------------------------------------------------------------------------------------------------------------------*/
#ifndef MOVE_EVENT_H_
#define MOVE_EVENT_H_
namespace Marx
{
	
	struct MoveMessage
    {
        EventType type;
        float x;
	float y;
	bool forced;
    };
/*
* Event Class
*/
	class MoveEvent: Event
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
