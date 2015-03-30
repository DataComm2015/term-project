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
        std::vector<Event> eventQueue;
    public:
        std::vector<Event> getEvents();
        virtual void addEvent(Event ev);
        void clearEvents()
        {
          eventQueue.clear();
        }
    };
}

#endif /* CONTROLLER_H_ */
