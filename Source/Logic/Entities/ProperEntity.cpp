#include "ProperEntity.h"
#include "../Event.h"

ProperEntity::ProperEntity( Marx::Map * map, float x, float y, Marx::Controller * ctrl = NULL, float h = 1.0, float w = 1.0  ) :
    Entity( map, x, y, ctrl, h, w )
{
}

void ProperEntity::onUpdate()
{
    // no nothing
}
