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


#ifndef STD_SET_
#define STD_SET_
#include <set>
#endif


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller
{
    private:

        std::set<int> eventQueue;

    public:
    
        std::set<int> getEvents();
};

#endif