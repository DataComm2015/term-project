#include "ProperEntity.h"
#include "../Event.h"

ProperEntity::ProperEntity( Marx::Map * map, float x, float y, Marx::Controller * ctrl = NULL, float h = 1.0, float w = 1.0  ) :
    Entity( map, x, y, ctrl, h, w )
{
    printf("ProperEntity: hello\n");
}

void ProperEntity::onUpdate()
{
    printf("ProperEntity::onUpdate:cont: %p:%d\n",getController(),getController()->getEvents()->size());
    // std::vector<Marx::Event*>* eventQueue = getController()->getEvents();

    // if(eventQueue->empty())
    // {
    //     return;
    // }
    // /*for( std::vector< Marx::Event* >::iterator it = eventQueue->begin()
    //    ; it != eventQueue->end()
    //    ; ++it )*/
    // while(eventQueue->size() > 0)
    // {
    //     // switch on type
    //     switch(eventQueue->at(0)->type)
    //     {
    //     case ::Marx::MOVE:
    //         MoveEvent* ev = (MoveEvent*)eventQueue->at(0);
    //         printf( "move: x:%f y:%f force:%d\n",
    //             ev->getX(), ev->getY(), ev->forced() );
    //         move( ev->getX(), ev->getY(), ev->forced() );
    //         MoveEvent *me = new MoveEvent(ev->getX(),ev->getY(),ev->forced());
    //         getController()->addEvent(me);
    //         break;
    //     }
    //     eventQueue->erase(eventQueue->begin());
    // }

    // getController()->clearEvents();
}
