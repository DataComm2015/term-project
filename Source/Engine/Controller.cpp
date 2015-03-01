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
-- REVISIONS: February 20, 2015
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- NOTES:
--        This file implements the generic controler class.
--
----------------------------------------------------------------------------------------------------------------------*/

#include "Controller.h"

using namespace Marx;
/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: std::vector<Event> Controller::getEvents()
--
-- DATE: February 19, 2015
--
-- REVISIONS: Feburary 20, 2015 - Revised to meet design - Marc
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Michael Chimick
--	       Marc Vouve 
--
-- INTERFACE: std::vector<Marx::Event> Controller::getEvents()
--
-- RETURNS: std::vector<Marx::Event> // A set holding the event queue in the controller
--
-- NOTES:
--        This function returns the eventQueue member of the Controller object
--
----------------------------------------------------------------------------------------------------------------------*/
std::vector<Event> Controller::getEvents()
{
    return eventQueue;
}
