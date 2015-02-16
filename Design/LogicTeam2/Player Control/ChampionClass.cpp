/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ChampionClass.cpp
--
-- PROGRAM: 4981 game project
--
-- FUNCTIONS:
-- void Champion::Champion( int jobclass, GameMap gmap, int x, int y )
-- void Champion::SetPosition( int x, int y )
-- void Champion::ResetEXP()
-- void Champion::EXPup( int exp )
-- int Champion::GetEXP()
-- int Champion::GetLevel()
-- void Champion::ResetHP()
-- void Champion::HPup( int hp )
-- void Champion::HPdown( int hp )
-- int Champion::GetHP()
-- int Champion::GetMaxHP()
-- void Champion::ResetAttackPower()
-- void Champion::AttackPowerUp( int attackpower )
-- void Champion::AttackPowerDown( int attackpower )
-- int Champion::GetAttackPower()
-- int Champion::GetDefaultAttackPower()
-- void Champion::ResetDefense()
-- void Champion::DefenseUp( int defense )
-- void Champion::DefenseDown( int defense )
-- void Champion::ResetSpeed()
-- void Champion::SpeedUp( int speed )
-- void Champion::SpeedDown( int speed )
-- int Champion::GetSpeed()
-- int Champion::GetDefaultSpeed()
-- bool Champion::CheckDeath()
-- void Champion::Move( int direction )
-- void Champion::SwitchNormalWeapon()
-- void Champion::NormalAttack( int x, int y )
-- void Champion::ShortCoolDownAbility( int x, int y )
-- int Champion::ShortCoolDownTimeLeft()
-- void Champion::MediumCoolDownAbility( int x, int y )
-- int Champion::MediumCoolDownTimeLeft()
-- void Champion::LongCoolDownAbility( int x, int y )
-- int Champion::LongCoolDownTimeLeft()
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ResetEXP
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::ResetEXP()
--
-- RETURNS: nothing
--
-- NOTES:
-- Resets a champion's EXP so it's 0 and the champion is at level 1
----------------------------------------------------------------------------------------------------------------------*/
void Champion::ResetEXP()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: EXPup
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::EXPup( int exp )
-- int exp: the amount of exp increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function adds the given EXP to current EXP count
----------------------------------------------------------------------------------------------------------------------*/
void Champion::EXPup( int exp )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetEXP
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetEXP()
--
-- RETURNS: EXP in integer format
--
-- NOTES:
-- This function gets the current amount of EXP the champion has
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetEXP()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetLevel
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetLevel()
--
-- RETURNS: the champion's level as an integer
--
-- NOTES:
-- This function converts the current EXP amount into its corresponding level. Amounts may vary according to job class.
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetLevel()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ResetHP
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::ResetHP()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the champion's HP to the current level's maximum HP
----------------------------------------------------------------------------------------------------------------------*/
void Champion::ResetHP()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: HPup
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::HPup( int hp )
-- int hp: the amount of HP to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the champion's HP, but not above the current level's maximum HP. Used as a healing function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::HPup( int hp )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: HPdown
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::HPdown( int hp )
-- int hp: the amount of HP to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decrease the champion's HP, but not below 0. Used as a take-damage function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::HPdown( int hp )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetHP
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetHP()
--
-- RETURNS: current HP as an integer
--
-- NOTES:
-- This function returns the current HP the champion has
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetHP()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetMaxHP
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetMaxHP()
--
-- RETURNS: Max HP as an integer
--
-- NOTES:
-- This function returns the maximum HP the champion can have at the current level
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetMaxHP()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ResetAttackPower
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::ResetAttackPower()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the champion's attack power to what's normal for the current level
----------------------------------------------------------------------------------------------------------------------*/
void Champion::ResetAttackPower()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: AttackPowerUp
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::AttackPowerUp( int attackpower )
-- int attackpower: the amount of attack power to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the champion's attack power. Used as a power up function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::AttackPowerUp( int attackpower )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: AttackPowerDown
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::AttackPowerDown( int attackpower )
-- int attackpower: the amount of attack power to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decreases the champion's attack power, but not below 0.. Used as a power down function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::AttackPowerDown( int attackpower )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetAttackPower
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetAttackPower()
--
-- RETURNS: Attack power as an integer
--
-- NOTES:
-- This function returns the champion's current attack power.
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetAttackPower()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetDefaultAttackPower
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetDefaultAttackPower()
--
-- RETURNS: default attack power for the level as an integer
--
-- NOTES:
-- This function returns the default attack power for the current level
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetDefaultAttackPower()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ResetDefense
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::ResetDefense()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the champion's defense to what's normal for the current level.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::ResetDefense()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: DefenseUp
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::DefenseUp( int defense )
-- int defense: the amount of defense to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the champion's defense. Used as a power up function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::DefenseUp( int defense )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: DefenseDown
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::DefenseDown( int defense )
-- int defense: the amount of defense to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decreases the champion's defense, but not below 0. Used as a power down function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::DefenseDown( int defense )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetDefense
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetDefense()
--
-- RETURNS: current defense as an integer
--
-- NOTES:
-- This function returns the current defense the champion has
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetDefense()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetDefaultDefense
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetDefaultDefense()
--
-- RETURNS: default defense for the level as an integer
--
-- NOTES:
-- This function returns the default defense for the current level
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetDefaultDefense()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ResetSpeed
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::ResetSpeed()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the champion's speed to what's normal for the current level.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::ResetSpeed()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: SpeedUp
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::SpeedUp( int speed )
-- int speed: the amount of speed to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the champion's speed. Used as a power up function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::SpeedUp( int speed )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: SpeedDown
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::SpeedDown( int speed )
-- int speed: the amount of speed to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decreases the champion's speed, but not below 0. Used as a power down function.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::SpeedDown( int speed )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetSpeed
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetSpeed()
--
-- RETURNS: current speed as an integer
--
-- NOTES:
-- This function returns the current speed the champion has
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetSpeed()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GetDefaultSpeed
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::GetDefaultSpeed()
--
-- RETURNS: default speed for the level as an integer
--
-- NOTES:
-- This function returns the default speed for the current level
----------------------------------------------------------------------------------------------------------------------*/
int Champion::GetDefaultSpeed()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: CheckDeath
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: bool Champion::CheckDeath()
--
-- RETURNS: whether the champion is dead as a boolean value
--
-- NOTES:
-- This function checks to see if the champion's HP has reached 0. If true, return 0 and maybe call death animation.
----------------------------------------------------------------------------------------------------------------------*/
bool Champion::CheckDeath()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Move
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::Move( int direction )
-- int direction: the value of the direction to move in (0 to 7)
--
-- RETURNS: nothing
--
-- NOTES:
-- This function moves the champion to a new (x, y) according to direction and speed. Will probably call SetPosition.
-- The movement may fail because something is blocking the champion, or the champion is attempting to move off the 
-- edge of the map. If there's an upgrade/downgrade item on the target x, y and the champion successfully moved,
-- then the effect of the upgrade/downgrade item is applied to the champion.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::Move( int direction )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: SwitchNormalWeapon
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::SwitchNormalWeapon()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function switches the character's normal weapon between long range and short range.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::SwitchNormalWeapon()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: NormalAttack
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::NormalAttack( int x, int y )
-- int x, int y: the target position of the attack
--
-- RETURNS: nothing
--
-- NOTES:
-- This function attempts to launch a normal attack at the target coordinate. Depending on normal weapon type, the 
-- attack may fail because the target is out of range.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::NormalAttack( int x, int y )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ShortCoolDownAbility
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::ShortCoolDownAbility( int x, int y )
-- int x, int y: the target position of the ability
--
-- RETURNS: nothing
--
-- NOTES:
-- This function attempts to launch a short-cooldown ability at the target coordinate. The ability may fail because 
-- the target is out of range or the cooldown timer isn't finished yet.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::ShortCoolDownAbility( int x, int y )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ShortCoolDownTimeLeft
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::ShortCoolDownTimeLeft()
--
-- RETURNS: time remaining in integer format, should be counting milliseconds
--
-- NOTES:
-- This function returns the time left for the cooldown of the short-cooldown ability.
----------------------------------------------------------------------------------------------------------------------*/
int Champion::ShortCoolDownTimeLeft()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MediumCoolDownAbility
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::MediumCoolDownAbility( int x, int y )
-- int x, int y: the target position of the ability
--
-- RETURNS: nothing
--
-- NOTES:
-- This function attempts to launch a medium-cooldown ability at the target coordinate. The ability may fail because 
-- the target is out of range or the cooldown timer isn't finished yet.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::MediumCoolDownAbility( int x, int y )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MediumCoolDownTimeLeft
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::MediumCoolDownTimeLeft()
--
-- RETURNS: time remaining in integer format, should be counting milliseconds
--
-- NOTES:
-- This function returns the time left for the cooldown of the medium-cooldown ability.
----------------------------------------------------------------------------------------------------------------------*/
int Champion::MediumCoolDownTimeLeft()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: LongCoolDownAbility
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: void Champion::LongCoolDownAbility( int x, int y )
-- int x, int y: the target position of the ability
--
-- RETURNS: nothing
--
-- NOTES:
-- This function attempts to launch a long-cooldown ability at the target coordinate. The ability may fail because 
-- the target is out of range or the cooldown timer isn't finished yet.
----------------------------------------------------------------------------------------------------------------------*/
void Champion::LongCoolDownAbility( int x, int y )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: LongCoolDownTimeLeft
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Champion::LongCoolDownTimeLeft()
--
-- RETURNS: time remaining in integer format, should be counting milliseconds
--
-- NOTES:
-- This function returns the time left for the cooldown of the long-cooldown ability.
----------------------------------------------------------------------------------------------------------------------*/
int Champion::LongCoolDownTimeLeft()
{
}
