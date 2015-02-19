/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:
--
-- PROGRAM:
--
-- FUNCTIONS:
--
-- DATE:
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- NOTES:
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
    
        std::set<int> GetEvents();
};

#endif