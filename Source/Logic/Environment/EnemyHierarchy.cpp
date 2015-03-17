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
	state = TOP;
	hasRoot = false;
	string line;

	// While there is more data to read
	while (!dataFile->eof())
	{	
		constructNode(dataFile);
	}
}


EnemyHierarchy::~EnemyHierarchy()
{

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