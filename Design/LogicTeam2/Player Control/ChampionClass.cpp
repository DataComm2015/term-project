/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ChampionClass.cpp
--
-- PROGRAM: 4981 game project
--
-- FUNCTIONS:
-- 
--
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- NOTES:
-- This class file provides the functions needed to set up and modify champion status.
-- It also provides the functions to control a champion (movement and attack).
----------------------------------------------------------------------------------------------------------------------*/

class Champion
{
};

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Champion constructor
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::Champion( int jobclass, GameMap gmap, int x, int y )
-- int jobclass: the job class you wish to set up the champion as
-- GameMap gmap: the game map the champion is on
-- int x, int y: the coordinates of the champion on the map
--
-- RETURNS: nothing
--
-- NOTES:
-- This function is used to generate a champion and set up its position on the game map
----------------------------------------------------------------------------------------------------------------------*/
void Champion::Champion( int jobclass, GameMap gmap, int x, int y )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: SetPosition
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::SetPosition( int x, int y )
-- int x, int y: the coordinates to set the champion on the map
--
-- RETURNS: nothing
--
-- NOTES:
-- This function is used to directly position a champion on a map, can be used for teleportation
----------------------------------------------------------------------------------------------------------------------*/
void Champion::SetPosition( int x, int y )
{
}


void Champion::ResetEXP()
{
}

void Champion::EXPup( int exp )
{
}

void Champion::ResetHP()
{
}

void Champion::HPup( int hp )
{
}

void Champion::HPdown( int hp )
{
}

int Champion::GetHP()
{
}

void Champion::ResetAttackPower()
{
}

void Champion::AttackPowerUp( int attackpower )
{
}

void Champion::AttackPowerDown( int attackpower )
{
}

int Champion::GetAttackPower()
{
}

void Champion::ResetDefense()
{
}

void Champion::DefenseUp( int defense )
{
}

void Champion::DefenseDown( int defense )
{
}

void Champion::SetSpeed( int hp )
{
}

void Champion::SpeedUp( int speed )
{
}

void Champion::SpeedDown( int speed )
{
}

bool Champion::CheckDeath()
{
}

void Champion::Move( int direction )
{
}

void Champion::SwitchNormalWeapon()
{
}

void Champion::NormalAttack( int x, int y )
{
}

void Champion::ShortCoolDownAbility( int x, int y )
{
}

void Champion::MediumCoolDownAbility( int x, int y )
{
}

void Champion::LongCoolDownAbility( int x, int y )
{
}