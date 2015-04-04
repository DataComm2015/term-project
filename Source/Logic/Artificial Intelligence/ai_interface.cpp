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
#include "Behaviour.h"
#include "../Entities/Vessel.h"
#include "../GateKeeperSource/src/GateKeeper.h"
#include "../../Engine/Cell.h"
#include <vector>
#include <cmath>

class AI : public Behaviour
{
	private:
		std::vector<Vessel> vesselList;	//to be removed later when a globally-accessible list becomes available
		std::vector<Vessel> targetList;
		double aggro_radius;
		GateKeeper* gateKeeper;

	public:
		AI(GateKeeper* g);
		~AI();
		virtual Entity Move();
		virtual void Attack(Vessel v);
		virtual void Search();
		virtual double CheckDistance(GateKeeper g, Vessel v);
		virtual Marx::Cell GetTargetLocation(Vessel v);
		virtual void Die();

	private:

};

AI::AI(GateKeeper* g)
{
	gateKeeper = g;
	aggro_radius = 1.0;
}

//returns the distance between the gateKeeper and Entity e
//distance =  (xA − xB)2 + (yA − yB)2
//future TO DO: sort all players by distance before adding them to the target list
double CheckDistance(GateKeeper g, Vessel v)
{
	double distance = abs((g.left- v.left) * (g.left - v.left)
									+ (g.top - v.top) * (g.top - v.top));
	return distance;
}



//checks the distance between the entity and each player, and adds players to a target list if true
void Search()
{
	//for each player
	for (auto it = vesselList.begin(); it != vesselList.end(); ++it)
	{
			//if the player is still alive
			if ( it->getHP() > 0)
			{
				//if the player is within the visual radius
				if ( CheckDistance(gateKeeper*, (*it)) < aggro_radius )
				{
					//add the player to the target list
					targetList.push_back(*it);
				}
				//check for players who have left the visual radius and remove them
			}
	}
}
