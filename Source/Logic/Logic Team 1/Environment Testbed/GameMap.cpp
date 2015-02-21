#include "GameMap.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>

using std::max;
using std::vector;


/******************************************************************************
*	FUNCTION: GameMap
*
*	DATE: February 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: GameMap(Cell **cMap, int w, int h);
*
*	PARAMETERS:
*		cMap - the cell map to use with the class
*		w - the width of the cell map
*		h - the height of the cell map
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the primary constructor of the GameMap class. 
*
*		This constructor defines the cell map that the GameMap will use.
******************************************************************************/
GameMap::GameMap(Cell **cMap, int w, int h)
{
	cellMap = cMap;
	width = w;
	height = h;
	bWidth = 0;
	bHeight = 0;
}


/******************************************************************************
*	FUNCTION: ~GameMap
*
*	DATE: February 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: ~GameMap();
*
*	PARAMETERS:
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the destructor for the GameMap. It destroys the
*		block map.
******************************************************************************/
GameMap::~GameMap()
{
	delete [] blockMap;
}


/******************************************************************************
*	FUNCTION: generateMap
*
*	DATE: February 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: bool generateMap();
*
*	PARAMETERS:
*
*	RETURNS:
*		bool - success or failure
*
*	NOTES:
*		This function is responsible for initiating and orchestrating
*		the process of generating a map to start a new round.
******************************************************************************/
bool GameMap::generateMap()
{
	// Create a block map
	if (!createBlockMap())
	{
		return false;
	}

	// Define map zones
	generateZones();

	// Place the boss

	// Place the players
	generatePlayers();

	// Place mini-bosses
    generateMiniBosses();
    
	// Define placeholder blocks
	generatePlaceholderBlocks();

	// Generate enemies

	// Generate miscellaneous objects

	// Generate tiles


	return true;
}


/******************************************************************************
*	FUNCTION: createBlockMap
*
*	DATE: February 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: bool createBlockMap();
*
*	PARAMETERS:
*
*	RETURNS:
*		bool - success or failure
*
*	NOTES:
*		This function creates a block data structure from the cell map
*		stored in the class. It also validates the cell map to ensure
*		that it fits the requirements.
******************************************************************************/
bool GameMap::createBlockMap()
{
	// Calculate the dimensions in block units
	bWidth = width / BLOCK_WIDTH;
	bHeight = height / BLOCK_HEIGHT;

	// If the width or height is not evenly divisible by the block size
	if (width % BLOCK_WIDTH != 0 || height % BLOCK_HEIGHT != 0)
	{
		return false;
	}

	// If the width or height is not an odd number of blocks
	if (bWidth % 2 == 0 || bHeight % 2 == 0)
	{
		return false;
	}

	// If the game map is not at least 5 blocks wide and tall
	if (bWidth < 5 || bHeight < 5)
	{
		return false;
	}

	// Create the block 2D array
	blockMap = new Block*[bHeight];

	for (int i = 0; i < bHeight; i++)
	{
		blockMap[i] = new Block[bWidth];
	}

	// Assign cell chunks to the block map
	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			// Retrieve the subgroup of cells

			// Assign the cells to the block
		}
	}

	return true;
}


/******************************************************************************
*	FUNCTION: generateZones
*
*	DATE: February 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void generateZones();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function calculates the size of each map zone and assigns
*		blocks in the zone to their corresponding map type.
******************************************************************************/
void GameMap::generateZones()
{
	// Find the centre of the map
	int wCentre = bWidth / 2;
	int hCentre = bHeight / 2;

	// Set the central block to the Arbiter zone
	blockMap[hCentre][wCentre].setZone(ARBITER);
	blockMap[hCentre][wCentre].setType(BOSS);

	// Calculate the width and height of the Stone zone
	stoneWidth = max(3, int(ceil(bWidth * 0.4)));
	stoneHeight = max(3, int(ceil(bHeight * 0.4)));

	// If the resulting width or height is even, add one to the dimension
	if (stoneWidth % 2 == 0)
	{
		stoneWidth++;
	}

	if (stoneHeight % 2 == 0)
	{
		stoneHeight++;
	}

	// Calculate the starting x and y for the stone zone
	int xStone = wCentre - stoneWidth / 2;
	int yStone = hCentre - stoneHeight / 2;

	// Set the ring outside the Arbiter zone to Stone blocks
	for (int i = yStone; i < yStone + stoneHeight; i++)
	{
		for (int j = xStone; j < xStone + stoneWidth; j++)
		{
			if (!(i == hCentre && j == wCentre))
			{
				blockMap[i][j].setZone(STONE);
			}
		}
	}
}


/******************************************************************************
*   FUNCTION: generatePlayers
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen
*   
*   PROGRAMMER: Chris Klassen
*   
*   INTERFACE: void generatePlayers();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       void
*   
*   NOTES:
*     This function randomly selects a player for each corner of
*	  the map and assigns them to that block.
******************************************************************************/
void GameMap::generatePlayers()
{
	int freePlayers = NUM_PLAYERS;
	vector<BlockType> players({P1, P2, P3, P4});

	// Loop through each block and assign a player to it
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		int nextPlayer = rand() % freePlayers;
		freePlayers--;

		switch(i)
		{
			case 0:
			{
				// Corner 1
				blockMap[0][0].setType(players[nextPlayer]);
				break;
			}

			case 1:
			{
				// Corner 2
				blockMap[bHeight - 1][0].setType(players[nextPlayer]);
				break;
			}

			case 2:
			{
				// Corner 3
				blockMap[0][bWidth - 1].setType(players[nextPlayer]);
				break;
			}

			case 3:
			{
				// Corner 4
				blockMap[bHeight - 1][bWidth - 1].setType(players[nextPlayer]);
				break;
			}
		}

		// Remove the selected player from the list of possible players
		players.erase(players.begin() + nextPlayer);
	}
}


/******************************************************************************
*   FUNCTION: generateMiniBosses
*   
*   DATE: February 15, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen, Julian Brandrick
*   
*   PROGRAMMER: Julian Brandrick, Chris Klassen
*   
*   INTERFACE: void generateMiniBosses();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       void
*   
*   NOTES:
*     This function places Mini-Bosses in certain points of the map, depending
*     on its size:
*       -> In the middle of each Grass edge
*       -> Each corner of the Stone zone
*       -> If the width of the Stone zone is greater than 3
*           -> Place a Mini-Boss in the middle top/bottom of the Stone zone
*       -> If the height of the Stone zone is greater than 3
*           -> Place a Mini-Boss in the middle left/right of the Stone zone
******************************************************************************/
void GameMap::generateMiniBosses()
{
    int xStone = (bWidth / 2) - (stoneWidth / 2);
    int yStone = (bHeight / 2) - (stoneHeight / 2);

    int xMiniBoss = stoneWidth - 1;
    int yMiniBoss = stoneHeight - 1;

    // If the Stone width is greater than 3
    //      -> Place a Mini-Boss in the middle top/bottom
    if(stoneWidth > 3)
    {
        xMiniBoss = stoneWidth / 2;
    }
    // If the Stone height is greater than 3
    //      -> Place a Mini-Boss in the middle left/right
    if(stoneHeight > 3)
    {
        yMiniBoss = stoneHeight / 2;
    }

    // Place Mini-Bosses in the Stone zone
    // Won't place the last Mini-Bosses if the width or height is even
    for(int i = yStone; i < yStone + stoneHeight; i += yMiniBoss)
    {
        for(int j = xStone; j < xStone + stoneWidth; j += xMiniBoss)
        {
        	// If this is not the arbiter zone
        	if (!(i == bHeight / 2 && j == bWidth / 2))
			{
            	blockMap[i][j].setType(MINIBOSS);
            }
        }
    }

    // If the width is even
    //      -> Place Mini-Bosses in the right Stone row
	if(stoneWidth % 2 == 0)
	{
		blockMap[yStone][xStone + stoneWidth - 1].setType(MINIBOSS);
		blockMap[yStone + (stoneHeight / 2)][xStone + stoneWidth - 1].setType(MINIBOSS);
		blockMap[yStone + stoneHeight - 1][xStone + stoneWidth - 1].setType(MINIBOSS);
	}

    // If the height is even
    //      -> Place Mini-Bosses in the bottom Stone row
	if(stoneHeight % 2 == 0)
	{
		blockMap[yStone + stoneHeight - 1][xStone].setType(MINIBOSS);
		blockMap[yStone + stoneHeight - 1][xStone + (stoneWidth / 2)].setType(MINIBOSS);
		blockMap[yStone + stoneHeight - 1][xStone + stoneWidth - 1].setType(MINIBOSS);
	}

    // Place Mini-Bosses in the middle of each Grass edge
    blockMap[0][bWidth / 2].setType(MINIBOSS);
    blockMap[bHeight - 1][bWidth / 2].setType(MINIBOSS);
    blockMap[bHeight / 2][0].setType(MINIBOSS);
    blockMap[bHeight / 2][bWidth - 1].setType(MINIBOSS);
}


/******************************************************************************
*   FUNCTION: generatePlaceholderBlocks
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen
*   
*   PROGRAMMER: Chris Klassen
*   
*   INTERFACE: void generatePlaceholderBlocks();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       void
*   
*   NOTES:
*     This function assigns each placeholder block a specific type.
*	  The type selection depends on the block's zone and surroundings.
******************************************************************************/
void GameMap::generatePlaceholderBlocks()
{
	int rRoll;

	// Loop through all blocks
	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			if (blockMap[i][j].getType() == EMPTY)
			{
				rRoll = (rand() % 100) + 1;

				blockMap[i][j].setType(makeBlockType(blockMap[i][j].getZone(), rRoll));
			}
		}
	}
}


/******************************************************************************
*   FUNCTION: makeBlockType
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen
*   
*   PROGRAMMER: Chris Klassen
*   
*   INTERFACE: BlockType makeBlockType(BlockZone z, int rRoll);
*   
*   PARAMETERS:
*		z - the zone of the block
*		rRoll - the randomly generated number to use in determination
*   
*   RETURNS:
*       BlockType - the type of zone selected for the block
*   
*   NOTES:
*     This function determines the type of block selected for the placeholder
*	  block based on the zone and random roll.
******************************************************************************/
BlockType GameMap::makeBlockType(BlockZone z, int rRoll)
{
	BlockType type;

	switch(z)
	{
		case GRASS:
		{
			if (rRoll < MAX_GRASS_ENEMIES)
			{
				type = ENEMIES;
			}
			else if (rRoll >= MAX_GRASS_ENEMIES && rRoll < MAX_GRASS_ENEMIES + MAX_GRASS_STRUCTURES)
			{
				type = STRUCTURE;
			}
			else
			{
				type = EMPTY;
			}

			break;
		}

		case STONE:
		{
			if (rRoll < MAX_STONE_ENEMIES)
			{
				type = ENEMIES;
			}
			else if (rRoll >= MAX_STONE_ENEMIES && rRoll < MAX_STONE_ENEMIES + MAX_STONE_STRUCTURES)
			{
				type = STRUCTURE;
			}
			else
			{
				type = EMPTY;
			}

			break;
		}
	}

	return type;
}


Cell** GameMap::getCellMap()
{
	return cellMap;
}


/******************************************************************************
*   FUNCTION: getBlockMap
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen
*   
*   PROGRAMMER: Chris Klassen
*   
*   INTERFACE: Block** getBlockMap();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       Block** - the block map used by the GameMap
*   
*   NOTES:
*     This function returns the block map used for map generation logic.
******************************************************************************/
Block** GameMap::getBlockMap()
{
	return blockMap;
}


/******************************************************************************
*   FUNCTION: getWidth
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen
*   
*   PROGRAMMER: Chris Klassen
*   
*   INTERFACE: int getWidth();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       int - the width of the GameMap
*   
*   NOTES:
*     This function returns the width of the game map.
******************************************************************************/
int GameMap::getWidth()
{
	return width;
}


/******************************************************************************
*   FUNCTION: getHeight
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Chris Klassen
*   
*   PROGRAMMER: Chris Klassen
*   
*   INTERFACE: int getHeight();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       int - the height of the GameMap
*   
*   NOTES:
*     This function returns the height of the game map.
******************************************************************************/
int GameMap::getHeight()
{
	return height;
}


/******************************************************************************
*   FUNCTION: getBlocksHor
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Julian Brandrick
*   
*   PROGRAMMER: Julian Brandrick
*   
*   INTERFACE: int getBlocksHor();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       int - the width of the GameMap in blocks.
*   
*   NOTES:
*     This function returns the width of the game map in blocks.
******************************************************************************/
int GameMap::getBlocksHor()
{
	return bWidth;
}


/******************************************************************************
*   FUNCTION: getBlocksVert
*   
*   DATE: February 17, 2015
*   
*   REVISIONS: (Date and Description)
*   
*   DESIGNER: Julian Brandrick
*   
*   PROGRAMMER: Julian Brandrick
*   
*   INTERFACE: int getBlocksVert();
*   
*   PARAMETERS:
*   
*   RETURNS:
*       int - the height of the GameMap in blocks.
*   
*   NOTES:
*     This function returns the height of the game map in blocks.
******************************************************************************/
int GameMap::getBlocksVert()
{
	return bHeight;
}