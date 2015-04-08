/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: GameMap.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--		GameMap(Map *cMap);
--		~GameMap();
--		bool generateMap(int seed, ServerGameScene *gs);
--		void cleanMap();
--		bool createBlockMap();
--		void setCellBoundaries();
--		void generateZones();
--		void generatePlayers();
--		void generateEnemies();
--		void createEnemyGroup(Block *block, BlockZone z, int num);
--		void getVesselPosition(int vesselNum, int *xPos, int *yPos);
--		void generateStructures();
--		ENTITY_TYPES getEnemyType(string enemy);
--		void generateMiniBosses();
--		void generatePlaceholderBlocks();
--		BlockType makeBlockType(BlockZone z, int rRoll);
--		void generateTiles();
--		Map* getCellMap();
--		Block** getBlockMap();
--		int getWidth();
--		int getHeight();
--
-- DATE: February 10, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Chris Klassen
--
-- PROGRAMMER:  Chris Klassen
--				Julian Brandrick
--
-- NOTES:
--        This file contains the implementation of the game's map.
--
--		  This includes all map generation, object placement, and tiling.
----------------------------------------------------------------------------------------------------------------------*/


#include "../ServerGameScene.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <set>
#include <iostream>
#include "EnemyHierarchy.h"
#include "../EntityFactory.h"
#include "../Entities/Structure.h"

using std::cout;
using std::endl;
using std::string;
using std::max;
using std::vector;
using std::set;

using namespace Marx;

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
*	INTERFACE: GameMap(Map *cMap);
*
*	PARAMETERS:
*		cMap - the cell map to use with the class
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the primary constructor of the GameMap class.
*
*		This constructor defines the cell map that the GameMap will use.
******************************************************************************/
GameMap::GameMap(Map *cMap)
{
	gameScene = NULL;
	cellMap = cMap;
	width = cMap->getWidth();
	height = cMap->getHeight();
	bWidth = 0;
	bHeight = 0;
	generated = false;
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
*	INTERFACE: bool generateMap(int seed, ServerGameScene *gs);
*
*	PARAMETERS:
*		seed - the seed to use to generate the map
*		gs - the server game scene object to use if on the server side
*
*	RETURNS:
*		bool - success or failure
*
*	NOTES:
*		This function is responsible for initiating and orchestrating
*		the process of generating a map to start a new round.
******************************************************************************/
bool GameMap::generateMap(int seed, ServerGameScene *gs)
{
	if (generated)
	{
		cleanMap();
		generated = false;
	}

    srand(seed);
    gameScene = gs;

	// Create a block map
	if (!createBlockMap())
	{
		cout << "Failed to generate block map" << endl;
		return false;
	}

	// Set cell boundaries
	setCellBoundaries();

	// Define map zones
	generateZones();

	// Place the boss
	if (gameScene != NULL)
	{
		// Place the players
		generatePlayers();

		// Place mini-bosses
	    generateMiniBosses();

		// Define placeholder blocks
		generatePlaceholderBlocks();

		// Generate enemies
		generateEnemies();

		// Generate miscellaneous objects
		generateStructures();
	}

	// Generate tiles
	if (gameScene == NULL)
	{
		generateTiles();
	}

	generated = true;

	return true;
}


/******************************************************************************
*	FUNCTION: cleanMap
*
*	DATE: April 3, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void cleanMap();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function removes all entities from the game map so that it can
*		be regenerated.
******************************************************************************/
void GameMap::cleanMap()
{
	Cell *tempCell;

	// Delete all entities
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tempCell = cellMap->getCell(j, i);

			// Retrieve the entities of the cell
			set<Entity*> entities = tempCell->getEntity();

			set<Entity*>::iterator it;
			for (it = entities.begin(); it != entities.end(); it++)
			{
				// Move entities to an unused cell
				(*it)->aMove(0, 0, false);

				// Delete all entities
				//delete (*it)->getController();

				//delete *it;
			}
		}
	}
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
			vector<Cell*> *cellGroup = new vector<Cell*>();

			for (int k = 0; k < BLOCK_HEIGHT; k++)
			{
				for (int l = 0; l < BLOCK_WIDTH; l++)
				{
					Cell *tempCell = cellMap->getCell(l + j * BLOCK_WIDTH, k + i * BLOCK_HEIGHT);
					cellGroup->push_back(tempCell);
				}
			}

			// Assign the cells to the block
			blockMap[i][j].setCells(cellGroup);
		}
	}

	return true;
}


/******************************************************************************
*	FUNCTION: setCellBoundaries
*
*	DATE: March 31, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void setCellBoundaries();
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function sets the outer rim of the game map to be non-
*		traversible.
******************************************************************************/
void GameMap::setCellBoundaries()
{
	// Set vertical boundaries
	for (int i = 0; i < height; i++)
	{
		cellMap->getCell(0, i)->setBlocking(true);
		cellMap->getCell(width - 1, i)->setBlocking(true);
	}

	for (int i = 0; i < width; i++)
	{
		cellMap->getCell(i, 0)->setBlocking(true);
		cellMap->getCell(i, height - 1)->setBlocking(true);
	}
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
*   FUNCTION: generateEnemies
*
*   DATE: March 17, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: void generateEnemies();
*
*   PARAMETERS:
*
*   RETURNS:
*       void
*
*   NOTES:
*     This function generates groupings of enemies for each enemy block in the
*     game map.
******************************************************************************/
void GameMap::generateEnemies()
{

	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			// If this block is an enemies block
			if (blockMap[i][j].getType() == ENEMIES)
			{
				int size = (rand() % MAX_ENEMY_GROUP) + MIN_ENEMY_GROUP;
				createEnemyGroup(&blockMap[i][j], blockMap[i][j].getZone(), size);
			}
		}
	}

}


/******************************************************************************
*   FUNCTION: createEnemyGroup
*
*   DATE: March 18, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: void createEnemyGroup(Block *block, BlockZone z, int num);
*
*   PARAMETERS:
*		block - the block to create in
*		z - the zone to use for creation
*		num - the number of enemies to create
*
*   RETURNS:
*       void
*
*   NOTES:
*		This function uses the enemy hierarchy to create groupings of enemies
*		based on the zone supplied.
******************************************************************************/
void GameMap::createEnemyGroup(Block *block, BlockZone z, int num)
{
	EnemyHierarchy *eh = EnemyHierarchy::getInstance();
	string enemy;
	Cell *cell;

	switch(z)
	{
		case GRASS:
		{
			int grassChoices = 4;
			int selection = rand() % grassChoices;

			switch(selection)
			{
				case 0:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "grass/lost_grass/ground_grass", true, 5);
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}

				case 1:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "grass/lost_grass/ground_grass");
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}

				case 2:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "grass/lost_grass");
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}

				case 3:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "grass/lost_grass", true, 1);
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}
			}

			break;
		}

		case STONE:
		{
			int stoneChoices = 3;
			int selection = rand() % stoneChoices;

			switch(selection)
			{
				case 0:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "stone/lost_stone");
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}

				case 1:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "grass/lost_grass/ground_grass");
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}

				case 2:
				{
					for (int i = 0; i < num; i++)
					{
						cell = block->getRandomCell();

						eh->getEnemy(&enemy, "stone/lost_stone", true, 1);
						gameScene->createEnemy(getEnemyType(enemy), NULL,
							cell->getX(), cell->getY());
					}

					break;
				}
			}

			break;
		}
	}

}


/******************************************************************************
*   FUNCTION: getVesselPosition
*
*   DATE: March 29, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: void getVesselPosition(int vesselNum, int *xPos, int *yPos);
*
*   PARAMETERS:
*		vesselNum - the vessel (0 - 3) to request
*		xPos - the destination for the x position
*		yPos - the destination for the y position
*
*   RETURNS:
*       void
*
*   NOTES:
*		This function returns the coordinates of a vessel on the game map.
******************************************************************************/
void GameMap::getVesselPosition(int vesselNum, int *xPos, int *yPos)
{
	BlockType vNum;

	// Identify the requested player
	if (vesselNum == 0)
	{
		vNum = P1;
	}
	else if (vesselNum == 1)
	{
		vNum = P2;
	}
	else if (vesselNum == 2)
	{
		vNum = P3;
	}
	else
	{
		vNum = P4;
	}

	// Loop through all blocks
	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			// If this is the block we are looking for
			if (blockMap[i][j].getType() == vNum)
			{
				Cell *tempCell = blockMap[i][j].getRandomCell();
				*xPos = tempCell->getX();
				*yPos = tempCell->getY();

				return;
			}
		}
	}
}


/******************************************************************************
*   FUNCTION: generateStructures
*
*   DATE: April 1, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: void generateStructures();
*
*   PARAMETERS:
*
*   RETURNS: void
*
*   NOTES:
*		This function creates structures on the map.
******************************************************************************/
void GameMap::generateStructures()
{
	EntityFactory *ef = EntityFactory::getInstance();
	Cell *destCell;

	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			// If this block is a structures block
			if (blockMap[i][j].getType() == STRUCTURE)
			{
				// Determine the number of structures to generate
				int numStructs = (rand() % MAX_STRUCTURE_GROUP) + MIN_STRUCTURE_GROUP;

				for (int k = 0; k < numStructs; k++)
				{
					// Get the destination cell
					destCell = blockMap[i][j].getRandomCell();

					// Place the structure
					gameScene->createStructure(STRUCTURES, destCell->getX(), destCell->getY());
					//cout << "Made entity at: " << destCell->getX() << ", " << destCell->getY() << endl;
				}
			}
		}
	}
}


/******************************************************************************
*   FUNCTION: getEnemyType
*
*   DATE: March 29, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: ENTITY_TYPES getEnemyType(string enemy);
*
*   PARAMETERS:
*		enemy - the enemy string to request the type for
*
*   RETURNS:
*       ENTITY_TYPES - the enum to return
*
*   NOTES:
*		This function converts a string to an enum for enemy types.
******************************************************************************/
ENTITY_TYPES GameMap::getEnemyType(string enemy)
{
	if (enemy.compare("wisp") == 0)
	{
		return MINION;
	}
	else if (enemy.compare("queen_bee") == 0)
	{
		return BASIC_TYPE;
	}
	else if (enemy.compare("bee") == 0)
	{
		return MINI_BEE;
	}
	else if (enemy.compare("wanderer") == 0)
	{
		return MINI_BOSS;
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


	// Loop through all blocks and place mini-bosses
    Cell *cell;
	EnemyHierarchy *eh = EnemyHierarchy::getInstance();
	string enemy;

    for (int i = 0; i < bHeight; i++)
    {
    	for (int j = 0; j < bWidth; j++)
    	{
    		if (blockMap[j][i].getType() == MINIBOSS)
    		{
    			// Place miniboss
    			cell = blockMap[j][i].getRandomCell();

				eh->getEnemy(&enemy, "grass/guardian_grass");
				gameScene->createEnemy(getEnemyType(enemy), NULL,
					cell->getX(), cell->getY());

				// Place miniboss enemies
				int num = (rand() % MAX_ENEMY_GROUP) + MIN_ENEMY_GROUP;

				for (int k = 0; k < num; k++)
				{
					cell = blockMap[j][i].getRandomCell();

					eh->getEnemy(&enemy, "grass/lost_grass/ground_grass/enemy_wisp");
					gameScene->createEnemy(getEnemyType(enemy), NULL,
						cell->getX(), cell->getY());
				}
    		}
    	}
    }
    
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



/******************************************************************************
*   FUNCTION: generateTiles
*
*   DATE: March 4, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: void generateTiles();
*
*   PARAMETERS:
*
*   RETURNS:
*       void
*
*   NOTES:
*     This function sets the correct tile ID for each cell in
*     the game map.
******************************************************************************/
void GameMap::generateTiles()
{
	// Base tiles
	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			BlockZone zone = blockMap[i][j].getZone();

			if (zone == GRASS)
			{
				blockMap[i][j].setTile(GRASS_1);
			}
			else if (zone == STONE)
			{
				blockMap[i][j].setTile(STONE_1);
			}
			else
			{
				blockMap[i][j].setTile(ARBITER_1);
			}
		}
	}


	// Decoration
	vector<CellTile> grassDecos({GRASS_D1, GRASS_D2, GRASS_D3, GRASS_D4, GRASS_D5, GRASS_D6});
	vector<CellTile> stoneDecos({STONE_D1, STONE_D2, STONE_D3});
	vector<CellTile> arbiterDecos({ARBITER_D1, ARBITER_D2, ARBITER_D3});

	for (int i = 0; i < bHeight; i++)
	{
		for (int j = 0; j < bWidth; j++)
		{
			BlockZone zone = blockMap[i][j].getZone();

			if (zone == GRASS)
			{
				blockMap[i][j].setDeco(&grassDecos);
			}
			else if (zone == STONE)
			{
				blockMap[i][j].setDeco(&stoneDecos);
			}
			else
			{
				blockMap[i][j].setDeco(&arbiterDecos);
			}
		}
	}


	// Grass edge tiles
	for (int i = 0; i < width; i++)
	{
		int offset = rand() % 4;
		cellMap->getCell(i, 0)->setTileId(GRASS_T1 + offset);
	}

	for (int i = 0; i < width; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(i, height - 1)->setTileId(GRASS_C1 + offset);
	}

	for (int i = 0; i < height; i++)
	{
		int offset = rand() % 3;
		cellMap->getCell(0, i)->setTileId(GRASS_L1 + (offset * 6));
	}

	for (int i = 0; i < height; i++)
	{
		int offset = rand() % 3;
		cellMap->getCell(width - 1, i)->setTileId(GRASS_R1 + (offset * 6));
	}


	// Stone edge tiles
	int stoneStartX = (width - stoneWidth * BLOCK_WIDTH) / 2;
	int stoneStartY = (height - stoneHeight * BLOCK_HEIGHT) / 2;

	for (int i = 0; i < stoneWidth * BLOCK_WIDTH; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(stoneStartX + i, stoneStartY)->setTileId(STONE_T1 + offset);
	}

	for (int i = 0; i < stoneWidth * BLOCK_WIDTH; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(stoneStartX + i, stoneStartY + (stoneHeight * BLOCK_HEIGHT) - 1)->setTileId(STONE_B1 + offset);
	}

	for (int i = 0; i < stoneHeight * BLOCK_HEIGHT; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(stoneStartX, stoneStartY + i)->setTileId(STONE_L1 + (offset * 4));
	}

	for (int i = 0; i < stoneHeight * BLOCK_HEIGHT; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(stoneStartX + (stoneWidth * BLOCK_WIDTH) - 1, stoneStartY + i)->setTileId(STONE_R1 + (offset * 4));
	}


	// Arbiter edge tiles
	int arbStartX = floor(width / 2) - floor(BLOCK_WIDTH / 2);
	int arbStartY = floor(height / 2) - floor(BLOCK_HEIGHT / 2);

	for (int i = 0; i < BLOCK_WIDTH; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(arbStartX + i, arbStartY)->setTileId(ARBITER_T1 + offset);
	}

	for (int i = 0; i < BLOCK_WIDTH; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(arbStartX + i, arbStartY + BLOCK_HEIGHT - 1)->setTileId(ARBITER_B1 + offset);
	}

	for (int i = 0; i < BLOCK_HEIGHT; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(arbStartX, arbStartY + i)->setTileId(ARBITER_L1 + (offset * 4));
	}

	for (int i = 0; i < BLOCK_HEIGHT; i++)
	{
		int offset = rand() % 2;
		cellMap->getCell(arbStartX + BLOCK_WIDTH - 1, arbStartY + i)->setTileId(ARBITER_R1 + (offset * 4));
	}


	// Grass Corner Tiles
	cellMap->getCell(0, 0)->setTileId(GRASS_TL);
	cellMap->getCell(width - 1, 0)->setTileId(GRASS_TR);
	cellMap->getCell(0, height - 1)->setTileId(GRASS_BL);
	cellMap->getCell(width - 1, height - 1)->setTileId(GRASS_BR);


	// Stone Corner Tiles
	cellMap->getCell(stoneStartX, stoneStartY)->setTileId(STONE_TL);
	cellMap->getCell(stoneStartX + (stoneWidth * BLOCK_WIDTH) - 1, stoneStartY)->setTileId(STONE_TR);
	cellMap->getCell(stoneStartX, stoneStartY + (stoneHeight * BLOCK_HEIGHT) - 1)->setTileId(STONE_BL);
	cellMap->getCell(stoneStartX + (stoneWidth * BLOCK_WIDTH) - 1, stoneStartY + (stoneHeight * BLOCK_HEIGHT) - 1)->setTileId(STONE_BR);


	// Arbiter Corner Tiles
	cellMap->getCell(arbStartX, arbStartY)->setTileId(ARBITER_TL);
	cellMap->getCell(arbStartX + (BLOCK_WIDTH) - 1, arbStartY)->setTileId(ARBITER_TR);
	cellMap->getCell(arbStartX, arbStartY + (BLOCK_HEIGHT) - 1)->setTileId(ARBITER_BL);
	cellMap->getCell(arbStartX + (BLOCK_WIDTH) - 1, arbStartY + (BLOCK_HEIGHT) - 1)->setTileId(ARBITER_BR);


	// Cliff edges
	cellMap->getCell(1, height - 1)->setTileId(GRASS_CL);
	cellMap->getCell(width - 2, height - 1)->setTileId(GRASS_CR);


	// Cliff Water Edge Tiles
	// for (int i = 0; i < width; i++)
	// {
	// 	int offset = rand() % 2;
	// 	cellMap->getCell(i, height - 1)->setTileId(WATER_C1 + offset);
	// }


	// Cliff Water Corner Tiles
	// cellMap->getCell(0, height - 1)->setTileId(NO_TILE);
	// cellMap->getCell(width - 1, height - 1)->setTileId(NO_TILE);

	// cellMap->getCell(1, height - 1)->setTileId(WATER_CL);
	// cellMap->getCell(width - 2, height - 1)->setTileId(WATER_CR);
}


/******************************************************************************
*   FUNCTION: getCellMap
*
*   DATE: February 17, 2015
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER: Chris Klassen
*
*   PROGRAMMER: Chris Klassen
*
*   INTERFACE: Map* getCellMap();
*
*   PARAMETERS:
*
*   RETURNS:
*       Map* - a pointer to the map object used by the game map.
*
*   NOTES:
*     This function returns the map used by the game map.
******************************************************************************/
Map* GameMap::getCellMap()
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
