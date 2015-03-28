/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	ai_interface.cpp -	An interface from which all AI classes will inherit
--
-- FUNCTIONS:
--		virtual ~AI();
--		virtual Entity Move();
--		virtual void Attack(Champion c);
--		virtual void Search();
--		virtual void Die();
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
-- search(), and die()) are presented here as virtual functions, which will be inherited by a specific AI class.
----------------------------------------------------------------------------------------------------------------------*/

class AI
{
	public:
		virtual ~AI();
		virtual Entity Move();
		virtual void Attack(Champion c);
		virtual void Search();
		virtual double CheckDistance();
		virtual Champion[] AddTarget(Champion c);
		virtual Champion[] RemoveTarget(Champion c);
		virtual Champion[] ChangeTarget(Champion c);
		virtual Cell GetTargetLocation(Champion c);
		virtual void Die();
		
	private:
		
};

