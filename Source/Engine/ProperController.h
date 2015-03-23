#ifndef PROPER_CONTROLLER_H
#define PROPER_CONTROLLER_H

#include "Controller.h"
#include "MoveEvent.h"

namespace Marx
{

    class ProperController : Controller
    {

    public:
	// takes move params and puts it in queue as proper event
	void addMoveEvent(float x, float y, bool forced);
	// network will override and do shiznit
	virtual void sendMoveUpdate(float x, float y, bool forced) = 0;

    };
}

#endif
