#ifndef SKILLS_H
#define SKILLS_H

#include "../Engine/VEntity.h"

/*----------------------------------------------------------------------------------------------------------------------
-- enum: SKILLTYPE
--
-- DATE: April 6, 2015
--
-- REVISIONS:
--
-- DESIGNER: Julian Brandrick
--
-- PROGRAMMER: Julian Brandrick
--
-- INTERFACE: enum class SKILLTYPE
--
-- NOTES:
--  Holds the different skill types
----------------------------------------------------------------------------------------------------------------------*/
enum class SKILLTYPE
{
    HEAL,
    DMG,
    BUFF,
    DEBUFF,
    BIGHEAL,
    SPAWN
};

/*----------------------------------------------------------------------------------------------------------------------
-- struct: skill
--
-- DATE: April 6, 2015
--
-- REVISIONS:
--
-- DESIGNER: Julian Brandrick
--
-- PROGRAMMER: Julian Brandrick
--
-- INTERFACE: struct skill
--
-- VARIABLES:
--      curX    -> The x coordinate of the skill event
--      curY    -> The y coordinate of the skill event
--      radius  -> The radius of the skill event
--      val     -> The value of the skill event
--      st      -> The type of the skill event
--
-- NOTES:
--  Contains all of the details of a skill event
----------------------------------------------------------------------------------------------------------------------*/
struct skill{
    float curX;
    float curY;
    int radius;
    int val;
    SKILLTYPE st;
};

/*----------------------------------------------------------------------------------------------------------------------
-- struct: skill_notify
--
-- DATE: April 6, 2015
--
-- REVISIONS:
--
-- DESIGNER: Julian Brandrick
--
-- PROGRAMMER: Julian Brandrick
--
-- INTERFACE: struct skill_notify
--
-- VARIABLES:
--      timer  -> Contains the duration of the skill graphic
--      entity -> Contains the skill graphic to be shown on the screen
--
-- NOTES:
--  Contains all of the details of displaying a graphic to the screen to notify all clients of a skill occuring
----------------------------------------------------------------------------------------------------------------------*/
struct skill_notify{
    int timer;
    Marx::VEntity *entity;
};

#endif
