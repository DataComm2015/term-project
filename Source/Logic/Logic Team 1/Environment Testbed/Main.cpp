#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Main.h"

using std::cout;
using std::cerr;
using std::endl;


/******************************************************************************
*	FUNCTION: main
*
*	DATE: February 9, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: int main(int argc, char* argv[]);
*
*	PARAMETERS:
*		argc - the number of command line arguments
*		argv - an array of command line arguments
*
*	RETURNS:
*		int - the termination code of the program
*
*	NOTES:
*		This is the main function of the test program. It creates
*		an array of cells and generates a fake game map using it.
******************************************************************************/
int main(int argc, char* argv[])
{
	// Validate command line arguments
	if (argc != 4)
	{
		cerr << "Invalid command line arguments." << endl;
		cerr << "Usage:" << endl << endl;
		cerr << "./mapgen [width in cells] [height in cells] [0 - display blocks, 1 - display cells]" << endl;
		exit(1);
	}

	// Randomize the seed
	srand(time(NULL));

	// Retrieve values from command line arguments
	int mWidth = atoi(argv[1]);
	int mHeight = atoi(argv[2]);
	int displayCells = atoi(argv[3]);

	// Create a 2D cell array
	Cell **cellMap = new Cell*[mHeight];

	for (int i = 0; i < mHeight; i++)
	{
		cellMap[i] = new Cell[mWidth];
	}

	// Create the GameMap object
	GameMap gMap(cellMap, mWidth, mHeight);

	// Generate a new map
	if (!gMap.generateMap())
	{
		cerr << "Map generation failed." << endl;
		delete [] cellMap;

		exit(1);
	}

	// Print the map in blocks
	printMap(&gMap, displayCells);

	// Delete the cell map memory
	delete [] cellMap;

	return 0;
}


/* This function prints out the game map */
void printMap(GameMap *gMap, bool displayCells)
{
	if (displayCells)
	{
		// Retrieve the list of cells
		Cell **cellMap = gMap->getCellMap();
		int w = gMap->getWidth();
		int h = gMap->getHeight();

		// Print the map
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cout << cellMap[i][j]() << " ";
			}

			cout << endl;
		}

		cout << endl;
	}
	else
	{
		// Retrieve the list of cells
		Block **blockMap = gMap->getBlockMap();
		int w = gMap->getBlocksHor();
		int h = gMap->getBlocksVert();

		// Print the map
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cout << blockMap[i][j]() << " ";
			}

			cout << endl;
		}

		cout << endl;
	}
}