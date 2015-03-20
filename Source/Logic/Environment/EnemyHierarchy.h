#ifndef ENEMY_HIERARCHY_H_
#define ENEMY_HIERARCHY_H_

#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

/* The data file containing the enemy hierarchy details */
#define SOURCE_FILE "./Logic/enemy_hierarchy.hdata"

/* The character indicating that a line is a comment */
#define COMMENT '#'

/* The character indicating the start of a node */
#define NODE_START '!'

/* The character that delimits a query string subsection */
#define QUERY_DELIMITER '/'

/* The phrase defining the top of the hierarchy */
#define NODE_TOP "null"

/* The phrase defining a node as a root */
#define NODE_ROOT "root"

/* The phrase defining a node as a leaf */
#define NODE_LEAF "leaf"

/* The default percent chance that a step up action can occur when retrieving an enemy */
#define STEP_UP_CHANCE 5

/* An enum to represent the possible types of nodes */
enum EnemyNodeType { ROOT, LEAF };
typedef enum EnemyNodeType EnemyNodeType;

/* A node in the enemy hierarchy */
struct EnemyNode
{
	struct EnemyNode* parent;
	std::vector<struct EnemyNode*>  children;
	std::string name;
	EnemyNodeType type;
	std::string enemyName;
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
		~EnemyHierarchy();

		bool getEnemy(std::string *dest, std::string enemyPath, bool stepUp = false, float stepUpChance = STEP_UP_CHANCE);

		static EnemyHierarchy* getInstance();
	private:
		void constructNode(std::ifstream *dataFile);
		void getWordsFromLine(std::vector<std::string> *wordList, std::ifstream *dataFile);
		int findNode(std::string nodeName);

		static EnemyHierarchy *instance;
		std::vector<EnemyNode *> nodeList;
		EnemyNode *root;
		bool hasRoot;
};


#endif