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
    public:
        virtual ~Controller();
        virtual std::vector<Event*>* getEvents();
        virtual void addEvent(Event *ev);
        virtual void clearEvents();
    private:
        std::vector<Event*> eventQueue;
    };
}

#endif /* CONTROLLER_H_ */
