#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include "Event.h"

namespace Marx
{
    /*
    * Controller class. Holds controller event queue
    */
    class Controller
    {
    protected:
        std::vector<Event*> eventQueue;
    public:
        std::vector<Event*>* getEvents();
        virtual void addEvent(Event *ev);
        void clearEvents()
        {
            while (eventQueue.size() != 0)
            {
                delete eventQueue.back();
                eventQueue.pop_back();
            }
        }
    };
}

#endif /* CONTROLLER_H_ */
