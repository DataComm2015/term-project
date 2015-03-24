#include "ProperController.h"

namespace Marx
{

    /*------------------------------------------------------------------------------
    -- FUNCTION:        NetworkController::addMoveEvent
    --
    -- DATE:            March 17, 2015
    --
    -- REVISIONS:       (Date and Description)
    --
    -- DESIGNER:        Jeff Bayntun
    --
    -- PROGRAMMER:      Jeff Bayntun
    --
    -- INTERFACE:       ProperController::addMoveEvent(float x, float y, bool forced)
    --                  x: x position to move to
                        y: y position to move to
                        forced: if move is forced

    -- RETURNS:         void
    --
    -- NOTES:           adds move event to the queue of events.
    ----------------------------------------------------------------------------------*/
	void Marx::ProperController::addMoveEvent(float x, float y, bool forced)
	{
		MoveEvent event(x, y, forced);
		eventQueue.push_back(event);
	}
	

}

