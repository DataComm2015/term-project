#ifndef ENEMY_HIERARCHY_H_
#define ENEMY_HIERARCHY_H_

#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>

/* The data file containing the enemy hierarchy details */
#define SOURCE_FILE "enemy_hierarchy.hdata"

/* The character indicating that a line is a comment */
#define COMMENT "#"

/* The character indicating the start of a node */
#define NODE "!"


/* An enum to represent the possible types of nodes */
enum EnemyNodeType { ROOT, LEAF };
typedef enum EnemyNodeType EnemyNodeType;

/* An enum to represent all enemies in the hierarchy */
enum EnemyNodeName { TEST1, TEST2, TEST3, TEST4 };
typedef enum EnemyNodeName EnemyNodeName;

/* A node in the enemy hierarchy */
struct EnemyNode
{
	struct EnemyNode* parent;
	std::string name;
	NodeType type;
	EnemyNodeName enemyName;
};

typedef struct EnemyNode EnemyNode;

/*
*	The EnemyHierarchy class is a singleton class containing functionality
*	that allows for semi-random selection of an enemy from a pre-defined hierarchy.
*/
class EnemyHierarchy
{
	public:
		EnemyHierarchy(std::ifstream *dataFile);
		static EnemyHierarchy* getInstance();
	private:
		void handleDataLine(std::string &line);

		static EnemyHierarchy *instance;
		
};


#endif