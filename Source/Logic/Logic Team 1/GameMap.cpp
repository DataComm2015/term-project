#include "GameMap.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using std::max;


/******************************************************************************
*  FUNCTION: GameMap
*
*  DATE: February 10, 2015
*
*  REVISIONS: (Date and Description)
*
*  DESIGNER: Chris Klassen
*
*  PROGRAMMER: Chris Klassen
*
*  INTERFACE: GameMap(Cell **cMap, int w, int h);
*
*  PARAMETERS:
*    cMap - the cell map to use with the class
*    w - the width of the cell map
*    h - the height of the cell map
*  RETURNS:
*
*    nothing
*
*  NOTES:
*    This is the primary constructor of the GameMap class.
*
*    This constructor creates a 2D array of cells to be manipulated.
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
*  FUNCTION: ~GameMap
*
*  DATE: February 11, 2015
*
*  REVISIONS: (Date and Description)
*
*  DESIGNER: Chris Klassen
*
*  PROGRAMMER: Chris Klassen
*
*  INTERFACE: ~GameMap();
*
*  PARAMETERS:
*
*  RETURNS:
*    nothing
*
*  NOTES:
*    This is the destructor for the GameMap. It destroys the
*    block map.
******************************************************************************/
GameMap::~GameMap()
{
    delete [] blockMap;
}


/******************************************************************************
*  FUNCTION: generateMap
*
*  DATE: February 10, 2015
*
*  REVISIONS: (Date and Description)
*
*  DESIGNER: Chris Klassen
*
*  PROGRAMMER: Chris Klassen
*
*  INTERFACE: bool generateMap();
*
*  PARAMETERS:
*
*  RETURNS:
*    bool - success or failure
*
*  NOTES:
*    This function is responsible for initiating and orchestrating
*    the process of generating a map to start a new round.
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

    // Place mini-bosses - Julian
    generateMiniBosses();

    // Define placeholder blocks

    // Generate enemies

    // Generate miscellaneous objects

    // Generate tiles


    return true;
}


/******************************************************************************
*  FUNCTION: createBlockMap
*
*  DATE: February 11, 2015
*
*  REVISIONS: (Date and Description)
*
*  DESIGNER: Chris Klassen
*
*  PROGRAMMER: Chris Klassen
*
*  INTERFACE: bool createBlockMap();
*
*  PARAMETERS:
*
*  RETURNS:
*    bool - success or failure
*
*  NOTES:
*    This function creates a block data structure from the cell map
*    stored in the class. It also validates the cell map to ensure
*    that it fits the requirements.
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
*  FUNCTION: generateZones
*
*  DATE: February 11, 2015
*
*  REVISIONS: (Date and Description)
*
*  DESIGNER: Chris Klassen
*
*  PROGRAMMER: Chris Klassen
*
*  INTERFACE: void generateZones();
*
*  PARAMETERS:
*
*  RETURNS:
*    void
*
*  NOTES:
*    This function calculates the size of each map zone and assigns
*    blocks in the zone to their corresponding map type.
******************************************************************************/
void GameMap::generateZones()
{
    // Find the centre of the map
    int wCentre = bWidth / 2;
    int hCentre = bHeight / 2;

    // Set the central block to the Arbiter zone
    blockMap[hCentre][wCentre].setZone(ARBITER);

    // Calculate the width and height of the Stone zone
    int wStone = max(3, int(ceil(bWidth * 0.4)));
    int hStone = max(3, int(ceil(bHeight * 0.4)));

    int xStone = wCentre - wStone / 2;
    int yStone = hCentre - hStone / 2;

    // Set the ring outside the Arbiter zone to Stone blocks
    for (int i = yStone; i < yStone + hStone; i++)
    {
        for (int j = xStone; j < xStone + wStone; j++)
        {
            if (!(i == hCentre && j == wCentre))
            {
                blockMap[i][j].setZone(STONE);
            }
        }
    }
}


/******************************************************************************
*  FUNCTION: generateMiniBosses
*
*  DATE: February 15, 2015
*
*  REVISIONS: (Date and Description)
*
*  DESIGNER: Chris Klassen
*
*  PROGRAMMER: Julian Brandrick
*
*  INTERFACE: void generateMiniBosses();
*
*  PARAMETERS:
*
*  RETURNS:
*    void
*
*  NOTES:
*    This function places Mini-Bosses in certain points of the map, depending
*    on its size:
*    	-> In the middle of each Grass edge
*    	-> Each corner of the Stone zone
*    	-> If the width of the Stone zone is greater than 3
*    		-> Place a Mini-Boss in the middle top/bottom of the Stone zone
*    	-> If the height of the Stone zone is greater than 3
*    		-> Place a Mini-Boss in the middle left/right of the Stone zone
******************************************************************************/
void GameMap::generateMiniBosses()
{
    // Calculate the width and height of the Stone zone
    int wStone = max(3, int(ceil(bWidth * 0.4)));
    int hStone = max(3, int(ceil(bHeight * 0.4)));

    int xStone = (bWidth / 2) - (wStone / 2);
    int yStone = (bHeight / 2) - (hStone / 2);

    int xMiniBoss = wStone - 1;
    int yMiniBoss = hStone - 1;

    if(wStone > 3)
    {
        xMiniBoss = wStone / 2;
    }
    if(hStone > 3)
    {
        yMiniBoss = hStone / 2;
    }

    for(int i = yStone; i < yStone + hStone; i += yMiniBoss)
    {
        for(int j = xStone; j < xStone + wStone; j += xMiniBoss)
        {
            blockMap[i][j].setEnemy(MINIBOSS);
        }
    }

    blockMap[0][bWidth / 2].setEnemy(MINIBOSS);
    blockMap[bHeight - 1][bWidth / 2].setEnemy(MINIBOSS);
    blockMap[bHeight / 2][0].setEnemy(MINIBOSS);
    blockMap[bHeight / 2][bWidth - 1].setEnemy(MINIBOSS);
}

Cell** GameMap::getCellMap()
{
    return cellMap;
}


Block** GameMap::getBlockMap()
{
    return blockMap;
}


int GameMap::getWidth()
{
    return width;
}

int GameMap::getHeight()
{
    return height;
}


int GameMap::getBlocksHor()
{
    return bWidth;
}

int GameMap::getBlocksVert()
{
    return bHeight;
}
