#ifndef PROPER_CONTROLLER_H
#define PROPER_CONTROLLER_H

#include "Controller.h"
#include "MoveEvent.h"

namespace Marx
{

    class ProperController : Controller
    {

    public:
	void addMoveEvent(float x, float y, bool forced);
    /**
     * To be overridden by children, specifically to send over the network
     */
	virtual void sendMoveUpdate(float x, float y, bool forced) = 0;

    };
}

#endif
