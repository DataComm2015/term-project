
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
--		     Marc Vouve
-- 
-- PROGRAMMER: Marc Rafanan
--			   Marc Vouve
-- 
-- NOTES:
-- This file defines the Event class members
-- 
----------------------------------------------------------------------------------------------------------------------*/
#ifndef EVENT_H_
#define EVENT_H_
namespace Marx
{
	
enum EventType
{
	MOVE,
	ATTACK
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
