#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include "Event.h"
#include "Entity.h"

namespace Marx
{
    class Entity;
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
        void setEntity(Entity* e);
        Entity* getEntity();
    private:
        Entity* entity;
        std::vector<Event*> eventQueue;
    protected:
        Entity * my_entity;
    };
}

#endif /* CONTROLLER_H_ */
