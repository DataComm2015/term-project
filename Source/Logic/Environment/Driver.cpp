#include "EnemyHierarchy.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

#define NUM_GROUPS 5
#define GROUP_SIZE 5

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::runtime_error;
using std::logic_error;


/*
*	A simple driver program testing the functionality of the enemy hierarchy.
*
*	Sample usage: "./EnemyHierarchy grass/lost_grass/ground_grass 1 5"
*		Query path, step-up allowed, 5% chance of step-up
*/
int main(int argc, char* argv[])
{
	string queryPath;
	bool stepUp = false;
	int stepUpChance = STEP_UP_CHANCE;

	// Validate command line arguments
	if (argc == 2)
	{
		queryPath = argv[1];
	}
	else if (argc == 3)
	{
		queryPath = argv[1];
		stepUp = atoi(argv[2]);
	}
	else if (argc == 4)
	{
		queryPath = argv[1];
		stepUp = atoi(argv[2]);
		stepUpChance = atoi(argv[3]);
	}
	else
	{
		cerr << "Invalid command line arguments." << endl;
		cerr << "USAGE: ./EnemyHierarchy [query path] [step-up 1 = true/0 = false OPTIONAL] [step-up chance OPTIONAL]" << endl;
		
		return 1;
	}
	
	// Randomize the seed
	srand(time(NULL));

	EnemyHierarchy *eh;

	try
	{
		eh = EnemyHierarchy::getInstance();
	}
	catch (logic_error &e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (runtime_error &e)
	{
		cerr << e.what() << endl;
		return 1;
	}

	// Retrieve a sample enemy
	string enemy;

	for (int i = 0; i < NUM_GROUPS; i++)
	{
		cout << "Group " << i << ": " << endl;

		for (int j = 0; j < GROUP_SIZE; j++)
		{
			if (eh->getEnemy(&enemy, queryPath, stepUp, (float) stepUpChance))
			{
				cout << enemy.c_str() << endl;
			}
			else
			{
				cerr << "Invalid query." << endl;
				return 1;
			}
		}
		
		cout << endl;
	}

	return 0;
}