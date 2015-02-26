/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Controller.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
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
--        This file defines the Controller class members
--
----------------------------------------------------------------------------------------------------------------------*/

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>

class Controller
{
    private:

        std::vector<Event> eventQueue;

    public:
    
        std::vector<Event> getEvents();
};

#endif
