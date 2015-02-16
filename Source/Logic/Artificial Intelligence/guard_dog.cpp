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

class GuardDog : public AI
{
	public:

		virtual ~AI();
		virtual Entity Move();
		virtual void Attack(Champion c);
		virtual void Search();
		virtual void Die();
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
void GuardDog::Search()
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