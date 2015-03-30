/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	guardDog.cpp -	The "guard dog" AI class
--
-- FUNCTIONS:
--
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- The AI interface provides the functions necessary for an given AI class to operate. Three functions (move(), attack(),
-- and search() are presented here as virtual functions, which will be inherited by a specific AI class.)
----------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <list>
#include <vector>

class GuardDog : public AI
{
	public:
		~AI();
		Entity Move();
		void Attack(Vessel v);
		void Search();
		void Die();
		
	private:
		int sightRange;
		std::vector<Vessel> playerList;
		std::vector<Vessel> targetList;
		
		
};

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GuardDog
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- The constructor for the GuardDog AI class.
----------------------------------------------------------------------------------------------------------------------*/
GuardDog::GuardDog()
{

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Move
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- INTERFACE: 
--
-- RETURNS: NULL if the next cell in its path is empty, otherwise returns the Entity that occupies the cell
--
-- NOTES:
-- Details the movement behaviour of Gatekeepers that implement the GuardDog AI class. 
----------------------------------------------------------------------------------------------------------------------*/
Entity GuardDog::Move()
{
	//need to find a good movement algorithm. A*?
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Attack
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- INTERFACE: void GuardDog::Attack(Champion c)
--  Champion c: the current champion that the gatekeeper will attack
--
-- NOTES:
-- Details the attack behaviour of Gatekeepers that implement the GuardDog AI class. This method is invoked when the
-- gatekeeper has a target champion and it is in range of its main attack.
----------------------------------------------------------------------------------------------------------------------*/
void GuardDog::Attack(Champion c) // Entity e?
{

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Search
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- Details the searching behaviour of Gatekeepers that implement the GuardDog AI class. The guard dog will search all
-- cells in a given radius of its spawn point. Any champions located in those cells will be added to an array of targets.
----------------------------------------------------------------------------------------------------------------------*/
void GuardDog::Search(int xpos, int ypos)
{
	double distance;

	//loop through a vector of all players in the game and add players to hitlist
	for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
	{
		distance = getDistance(playerList[i], xpos, ypos);
		if (distance < sight_range)
		{
			//if the player is in range, add the player to the target hit list
			vessel.push_back(playerList[i]);
		}
	}
	
	//iterate through the target list and remove players outside the guard dog's sight
	for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
	{
		distance = getDistance(targetList[i], xpos, ypos);
		if (distance > sight_range)
		{
			//if the player out of range, remove the player from the target hit list
			targetList.remove(targetList[i]);
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: CheckDistance
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- Checks the distance between the gatekeeper and the Champion to determine if an attack is feasible
----------------------------------------------------------------------------------------------------------------------*/
int GuardDog::CheckDistance(Champion C)
{

}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: addTarget
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- checks to see if champion c is already in the list of target characters, and adds it if it isn't.
----------------------------------------------------------------------------------------------------------------------*/
Champion[] GuardDog::AddTarget(Champion c)
{

}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: addTarget
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- removes champion c from the list of target characters. Used when the current target has left the gatekeeper's sight,
-- or has died.
----------------------------------------------------------------------------------------------------------------------*/
Champion[] GuardDog::RemoveTarget(Champion c)
{

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: changeTarget
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- changes current target to Champion c. Used when the current target has left the gatekeeper's sight, or has died.
----------------------------------------------------------------------------------------------------------------------*/
Champion[] GuardDog::ChangeTarget(Champion c)
{

}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getTargetLocation
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- returns the distance between the gatekeeper and vessel
----------------------------------------------------------------------------------------------------------------------*/
Cell GuardDog::GetDistance(int xpos, int ypos)
{

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Die
--
-- DATE: February 14, 2015
--
-- REVISIONS (Date and Description):
--
-- DESIGNERS: Sebastian Pelka
--
-- PROGRAMMERS: Sebastian Pelka
--
-- NOTES:
-- Do any clean up work needed such as calling destructors and freeing memory. Is called when the Gatekeeper is 
-- at less than 1 hit points.
----------------------------------------------------------------------------------------------------------------------*/
void GuardDog::Die()
{

}