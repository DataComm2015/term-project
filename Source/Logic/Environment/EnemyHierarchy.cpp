#include <sstream>
#include "EnemyHierarchy.h"

using std::ifstream;
using std::string;
using std::vector;
using std::runtime_error;
using std::logic_error;
using std::stringstream;


EnemyHierarchy* EnemyHierarchy::instance = nullptr;


/******************************************************************************
*	FUNCTION: EnemyHierarchy
*
*	DATE: March 14, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: EnemyHierarchy(ifstream *dataFile);
*
*	PARAMETERS:
*		dataFile - the source file to construct the hierarchy from
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This function creates an EnemyHierarchy from a data file.
******************************************************************************/
EnemyHierarchy::EnemyHierarchy(ifstream *dataFile)
{
	hasRoot = false;
	string line;

	// While there is more data to read
	while (!dataFile->eof())
	{	
		constructNode(dataFile);
	}
}


/******************************************************************************
*	FUNCTION: ~EnemyHierarchy
*
*	DATE: March 17, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: ~EnemyHierarchy();
*
*	PARAMETERS:
*
*	RETURNS:
*
*	NOTES:
*		This function deletes the nodes created for the hierarchy.
******************************************************************************/
EnemyHierarchy::~EnemyHierarchy()
{
	for (int i = 0; i < (int) nodeList.size(); i++)
	{
		delete nodeList[i];
	}
}


/******************************************************************************
*	FUNCTION: getEnemy
*
*	DATE: March 17, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: string getEnemy(string *dest, string enemyPath, bool stepUp, float stepUpChance);
*
*	PARAMETERS:
*		dest - the destination string for the retrieved enemy name
*		enemyPath - the '/' delimited path of the node you want to retrieve from
*		stepUp - whether or not to allow step-up operations (defaults to false)
*		stepUpChance - the percent chance (0 to 100) of a step up occurring
*
*	RETURNS:
*		bool - whether or not the query succeeded
*
*	NOTES:
*		This function is the core of the EnemyHierarchy. It can be used in a variety of ways
*		in order to retrieve an enemy from a sub-grouping of your choice. If you allow step-up
*		operations, the selection has a chance of 'stepping up' to one higher level in the
*		hierarchy in order to select an enemy from a slightly different path.
*
*		Example usages:
*			"grass/lost_grass/air_grass", stepUp = true, stepUpChance = 5
*				You will be given an enemy within the air_grass subgroup, with a 5% chance of an
*				enemy from lost_grass being selected instead. This might result in a ground_grass
*				enemy being chosen.
*
*			"stone/guardian_stone", stepUp = false
*				You will be given a miniboss from the stone zone with no chance of anything else.
******************************************************************************/
bool EnemyHierarchy::getEnemy(string *dest, string enemyPath, bool stepUp, float stepUpChance)
{
	// Parse the query string into a vector of substrings
	vector<string> query;

	while (true)
	{
		int dLocation = enemyPath.find(QUERY_DELIMITER);

		// If we are not yet at the last subsection
		if (dLocation != string::npos)
		{
			if (dLocation == 0)
			{
				// The string starts with a delimiter; we cannot recover
				return false;
			}

			if (enemyPath.size() > 1)
			{
				query.push_back(enemyPath.substr(0, dLocation));

				if (dLocation == enemyPath.size() - 1)
				{
					// There is nothing after this
					break;
				}

				enemyPath = enemyPath.substr(dLocation + 1, enemyPath.size());
			}
			else
			{
				// String ends with a delimiter; we can recover
				break;
			}
		}
		else
		{
			// This is our last query subsection
			query.push_back(enemyPath.substr(0, enemyPath.size()));
			break;	
		}
	}

	EnemyNode *currentNode = root;

	// Find the destination node
	for (int i = 0; i < (int) query.size(); i++)
	{
		EnemyNode *iterationNode = currentNode;

		for (int j = 0; j < (int) currentNode->children.size(); j++)
		{
			// If this node has a child with the queried name
			if (currentNode->children[j]->name.compare(query[i]) == 0)
			{
				currentNode = currentNode->children[j];
				break;
			}
		}

		// If we have not advanced since the last iteration
		if (iterationNode == currentNode)
		{
			return false;
		}
	}

	// If we have a chance of step-up
	if (stepUp)
	{
		int randChance = rand() % 100 + 1;
		if (randChance < stepUpChance)
		{
			// Move up one directory
			currentNode = currentNode->parent;
		}
	}

	// Move down through the hierarchy until we reach an enemy node
	while (currentNode->type != LEAF)
	{
		int randChild = rand() % currentNode->children.size();

		currentNode = currentNode->children[randChild];
	}

	// Return the selected enemy
	(*dest) = currentNode->enemyName;
	return true;
}

/******************************************************************************
*	FUNCTION: constructNode
*
*	DATE: March 14, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void constructNode(ifstream *dataFile);
*
*	PARAMETERS:
*		dataFile - the file to pull node information from
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function constructs a node from the data file.
******************************************************************************/
void EnemyHierarchy::constructNode(ifstream *dataFile)
{
	vector<string> words;
	getWordsFromLine(&words, dataFile);

	if (words.size() < 1 || words[0][0] == COMMENT)
	{
		// Empty line or comment
		return;
	}

	// Create a new node to work with
	EnemyNode *node = new EnemyNode;
	nodeList.push_back(node);

	// If we don't yet have a top node
	if (!hasRoot)
	{
		// Set the top node to this node
		root = node;
		hasRoot = true;

		getWordsFromLine(&words, dataFile);
		node->name = words[0];

		getWordsFromLine(&words, dataFile);
		
		if (words[0].compare(NODE_ROOT) == 0)
		{
			// this is not a leaf
			node->type = ROOT;
		}
		else
		{
			// This is a leaf
			node->type = LEAF;
			
			getWordsFromLine(&words, dataFile);
			node->enemyName = words[0];
		}
	}
	else
	{
		// Add a new hierarchy node
		EnemyNode *node = new EnemyNode;
		nodeList.push_back(node);

		// Assign parent and parent's children
		node->parent = nodeList[findNode(words[0])];
		node->parent->children.push_back(node);

		// Assign the name
		getWordsFromLine(&words, dataFile);
		node->name = words[0];

		// Assign the type
		getWordsFromLine(&words, dataFile);
		
		if (words[0].compare(NODE_ROOT) == 0)
		{
			// this is not a leaf
			node->type = ROOT;
		}
		else
		{
			// This is a leaf
			node->type = LEAF;
			
			getWordsFromLine(&words, dataFile);
			node->enemyName = words[0];
		}
	}
}


/******************************************************************************
*	FUNCTION: getWordsFromLine
*
*	DATE: March 14, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void getWordsFromLine(vector<string> *wordList, ifstream *dataFile);
*
*	PARAMETERS:
*		wordList - the destination list of words
*		dataFile - the file to pull from
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function retrieves a list of words on a line from a file.
******************************************************************************/
void EnemyHierarchy::getWordsFromLine(vector<string> *wordList, ifstream *dataFile)
{
	// Clear the word list
	wordList->clear();

	string line;
	string word;

	// Read a line from the data file
	getline(*dataFile, line);
	stringstream buffer(line);

	// Read all words from the string and put them in the list
	while (buffer >> word)
	{
		wordList->emplace_back(word);
	}
}


/******************************************************************************
*	FUNCTION: findNode
*
*	DATE: March 17, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: int findNode(string nodeName);
*
*	PARAMETERS:
*		nodeName - the name of the node to search for
*
*	RETURNS:
*		int - the index of the node, or -1 if it does not exist
*
*	NOTES:
*		This function searches for a node in the hierarchy.
******************************************************************************/
int EnemyHierarchy::findNode(string nodeName)
{
	for (int i = 0; i < (int) nodeList.size(); i++)
	{
		// If this is the node we are looking for
		if (nodeList[i]->name.compare(nodeName) == 0)
		{
			return i;
		}
	}

	return -1;
}


/******************************************************************************
*	FUNCTION: getInstance
*
*	DATE: March 14, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: EnemyHierarchy* getInstance();
*
*	PARAMETERS:
*
*	RETURNS:
*		EnemyHierarchy* - an instance of the class
*
*	NOTES:
*		This function returns an instance of the singleton class.
******************************************************************************/
EnemyHierarchy* EnemyHierarchy::getInstance()
{
	// If we do not already have an instance
	if (instance == nullptr)
	{
		// Check to see if the source file exists
		ifstream dataFile;
		dataFile.open(SOURCE_FILE);

		if (!dataFile.is_open())
		{
			// We cannot create the EnemyHierarchy
			throw runtime_error("Data file not found.");
		}

		// Create a new instance
		instance = new EnemyHierarchy(&dataFile);

		// Close the data file
		dataFile.close();
	}

	return instance;
}