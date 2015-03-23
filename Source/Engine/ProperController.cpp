#include "ProperController.h"

namespace Marx
{

	// takes move params and puts it in queue as proper event
	void Marx::ProperController::addMoveEvent(float x, float y, bool forced)
	{
		MoveEvent event(x, y, forced);
		eventQueue.push_back(event);
	}
	

}

