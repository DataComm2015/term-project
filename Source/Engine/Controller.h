#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include "Event.h"
#include "Entity.h"

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
        virtual void register_my_entity(Entity *);  // these don't follow normal convention so they wont intersect.
        virtual Entity * get_my_entity();
    private:
        std::vector<Event*> eventQueue;
    protected:
        Entity * my_entity;
    };
}

#endif /* CONTROLLER_H_ */
