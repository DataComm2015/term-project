
/**
 * constructs a new move event
 *
 * @param _x new n position the entity should move to
 * @param _y new y position that the entity should move to
 * @param f whatever forced means
 */
void Marx::MoveEvent::MoveEvent(float _x, float _y, bool f=false)
{
    x     = _x;
    y     = _y;
    force = f;
}

/**
 * returns the x property of the move event.
 *
 * @return   x property of the move event.
 */
float Marx::MoveEvent::getX()
{
    return x;
}

/**
 * returns the y property of the move event.
 *
 * @return   y property of the move event.
 */
float Marx::MoveEvent::getY()
{
    return y;
}

/**
 * returns the force property of the move event.
 *
 * @return   force property of the move event.
 */
bool Marx::MoveEvent::forced()
{
    return force;
}
