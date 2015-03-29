#include "ServerGameScene.h"
#include <iostream>
#include "ServerCommand.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

ServerGameScene::ServerGameScene(ServerCommand *command)
    : command(command)
{
	// Create the cell map
	cMap = new Map(25, 25);

	for (int i = 0; i < cMap->getHeight(); i++)
	{
		for (int j = 0; j < cMap->getWidth(); j++)
		{
			Cell *tempCell = new Cell();
			tempCell->setTileId(1);

			cMap->setCell(j, i, tempCell);
		}
	}

	gMap = new GameMap(cMap);

	// Generate the game map
	if (!gMap->generateMap())
	{
		cerr << "Invalid map dimensions." << endl;
	}

}

ServerGameScene::~ServerGameScene()
{
	delete gMap;

	for (int i = 0; i < cMap->getHeight(); i++)
	{
		for (int j = 0; j < cMap->getWidth(); j++)
		{
			delete cMap->getCell(j, i);
		}
	}

	delete cMap;
}

void ServerGameScene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void ServerGameScene::processEvents(sf::Event& e)
{
		
}

void ServerGameScene::draw()
{

}

void ServerGameScene::enterScene()
{
    printf("IN GAME SCENE\r\n");
}

