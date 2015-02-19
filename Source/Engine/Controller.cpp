/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Controller.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--            std::set<int> Controller::getEvents()
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- NOTES:
--        This file implements the Controller class members
--
----------------------------------------------------------------------------------------------------------------------*/

#include "Controller.h"


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: std::set<int> Controller::getEvents()
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: std::set<int> Controller::getEvents()
--
-- RETURNS: std::set<int> // A set holding the event queue in the controller
--
-- NOTES:
--        This function returns the eventQueue member of the Controller object
--
----------------------------------------------------------------------------------------------------------------------*/
std::set<int> Controller::getEvents()
{
    return eventQueue;
}