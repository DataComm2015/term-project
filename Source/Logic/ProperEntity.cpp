#include "ProperEntity.h"
#include "Event.h"

ProperEntity::ProperEntity( Marx::Map * map, float x, float y, Marx::Controller * ctrl = NULL, float h = 1.0, float w = 1.0  ) :
    Entity( map, x, y, ctrl, h, w )
    ,controller( ctrl )
{
    printf("ProperEntity: hello\n");
}

void ProperEntity::onUpdate()
{
    std::vector< Marx::Event > eventQueue = controller->getEvents();

    for( std::vector< Marx::Event >::iterator it = eventQueue.begin()
       ; it != eventQueue.end()
       ; ++it )
    {
        // switch on type
        switch(it->type)
        {
        case ::Marx::MOVE:
            MoveEvent* ev = (MoveEvent*) (&*it);
            printf( "move: x:%f y:%f force:%d\n",
                ev->getX(), ev->getY(), ev->forced() );
            move( ev->getX(), ev->getY(), ev->forced() );
            MoveEvent me(ev->getX(),ev->getY(),ev->forced());
            controller->addEvent(me);
            break;
        }
    }

    eventQueue.clear();
}
