#include <sstream>
#include "EnemyHierarchy.h"

using std::ifstream;
using std::string;
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
	string line;

	// While there is more data to read
	while (!dataFile->eof())
	{	
		// Read a line of data from the file
		getline(*dataFile, line);

		// Handle the line
		handleDataLine(line);
	}
}


/******************************************************************************
*	FUNCTION: handleDataLine
*
*	DATE: March 14, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void handleDataLine(std::string &line);
*
*	PARAMETERS:
*		line - the line to interpret
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function interprets a data line from a file.
******************************************************************************/
void EnemyHierarchy::handleDataLine(std::string &line)
{
	// If this line is a comment or empty
	if (line[0] = COMMENT || line.size() < 2)
	{
		// Do nothing
		return;
	}
	else
	{
		stringstream buffer(line);
		string word;
		buffer >> word;

		// If this is the start of a node
		if (word[0] == NODE)
		{
			
		}
	}
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