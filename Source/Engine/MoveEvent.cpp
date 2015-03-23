#include "MoveEvent.h"
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
/*------------------------------------------------------------------------------
	-- FUNCTION:        MoveEvent
	--
	-- DATE:            March 20, 2015
	--
	-- REVISIONS:       (Date and Description)
	--
	-- DESIGNER:        Jeff Bayntun
	--
	-- PROGRAMMER:      Jeff Bayntun
	--
	-- INTERFACE:       MoveEvent::MoveEvent(float _x, float _y, bool f)
	--                  _x -  x coordinate to move to 
			    _y -  y coordinate to move to 
			    f  -  is event forced (move even if collision)

	-- RETURNS:         void
	--
	-- NOTES:         
	----------------------------------------------------------------------------------*/
Marx::MoveEvent::MoveEvent(float _x, float _y, bool f)
{
	x = _x;
	y = _y;
	force = f;
}
/*------------------------------------------------------------------------------
	-- FUNCTION:        getX
	--
	-- DATE:            March 20, 2015
	--
	-- REVISIONS:       (Date and Description)
	--
	-- DESIGNER:        Jeff Bayntun
	--
	-- PROGRAMMER:      Jeff Bayntun
	--
	-- INTERFACE:       MoveEvent::getX()
	--                  

	-- RETURNS:         x coordinate this event moves entity to
	--
	-- NOTES:         
	----------------------------------------------------------------------------------*/
float Marx::MoveEvent::getX()
{
	return x;
}
/*------------------------------------------------------------------------------
	-- FUNCTION:        getY
	--
	-- DATE:            March 20, 2015
	--
	-- REVISIONS:       (Date and Description)
	--
	-- DESIGNER:        Jeff Bayntun
	--
	-- PROGRAMMER:      Jeff Bayntun
	--
	-- INTERFACE:       MoveEvent::getY()
	--                  

	-- RETURNS:         y coordinate this event moves entity to
	--
	-- NOTES:         
	----------------------------------------------------------------------------------*/
float Marx::MoveEvent::getY()
{
	return y;
}
/*------------------------------------------------------------------------------
	-- FUNCTION:        forced
	--
	-- DATE:            March 20, 2015
	--
	-- REVISIONS:       (Date and Description)
	--
	-- DESIGNER:        Jeff Bayntun
	--
	-- PROGRAMMER:      Jeff Bayntun
	--
	-- INTERFACE:       MoveEvent::forced()
	--                  

	-- RETURNS:         true if this move will occur even if a collision results.
	--
	-- NOTES:         
	----------------------------------------------------------------------------------*/
bool Marx::MoveEvent::forced()
{
	return forced;
}


