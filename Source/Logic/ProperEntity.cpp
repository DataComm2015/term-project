#include "ProperEntity.h"

ProperEntity::ProperEntity(Marx::Map* map,float x,float y,
    Marx::Controller* ctrl = NULL,float h = 1.0,float w = 1.0  )
    :Entity(map,x,y,ctrl,h,w)
    ,controller(ctrl)
{
}

void ProperEntity::onUpdate()
{
    std::vector<MoveEvent> eventQueue = controller->getEvents();

    for( auto it = eventQueue.begin()
       ; it != eventQueue.end()
       ; ++it )
    {
        // switch on type
        // move( it->getX(), it->getY(), it->forced() );
        printf( "move: x:%f y:%f force:%d\n", it->getX(), it->getY(), it->forced() );
    }

    eventQueue.clear();
}
