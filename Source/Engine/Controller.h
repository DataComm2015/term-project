#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include "Event.h"

namespace Marx
{  
    class Entity;
    /*
    * Controller class. Holds controller event queue
    */
    class Controller
    {
    public:
        Controller();
        virtual ~Controller();
        virtual std::vector<Event*>* getEvents();
        virtual void addEvent(Event *ev);
        virtual void clearEvents();
        void setEntity(Entity* e);
    private:
        std::vector<Event*> eventQueue;
        Entity* entity;
    };
}

#endif /* CONTROLLER_H_ */
