/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: PlayerController.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- NOTES:
--        This file defines the PlayerController class members
--
----------------------------------------------------------------------------------------------------------------------*/

#ifndef _CONTROLLER_H
#include "Controller.h"
#endif

#ifndef PLAYER_CONTROLLER_H_
#define PLAYER_CONTROLLER_H_

class PlayerController : Controller
{
    void onMouseButtonDown();
    void onKeyPressed();
};

#endif