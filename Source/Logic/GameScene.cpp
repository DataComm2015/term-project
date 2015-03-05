#include "GameScene.h"
#include <iostream>

using namespace Marx;

GameScene::GameScene() : renderer(AppWindow::getInstance(), 4000)
{
	// Create the cell map
	cMap = new Map(40, 40);

	for (int i = 0; i < cMap->getHeight(); i++)
	{
		for (int j = 0; j < cMap->getWidth(); j++)
		{
			Cell *tempCell = new Cell();
			tempCell->setTileId(rand() % 36 + 1);

			cMap->setCell(j, i, tempCell);
		}
	}

	gMap = new GameMap(cMap);

	// Set the Tile Manager active tileset
	try
	{
		tilemap = Manager::TileManager::load("Logic/Environment/map.tset");
	}
	catch(const char* e)
	{
		std::cerr << e << std::endl;
	}
	catch(std::string e)
	{
		std::cerr << e << std::endl;
	}

	cMap->setTexture(tilemap);
}

GameScene::~GameScene()
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

void GameScene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void GameScene::processEvents(sf::Event& e)
{
	if (e.type == sf::Event::Closed)
	{
		AppWindow::getInstance().close();
	}
	else if( e.type == sf::Event::KeyPressed )
	{
		// Generate the game map
		gMap->generateMap();

		for (int i = 0; i < cMap->getHeight(); i++)
		{
			for (int j = 0; j < cMap->getWidth(); j++)
			{
				Cell *tempCell = new Cell();
				tempCell->setTileId(rand() % 36 + 1);

				cMap->setCell(j, i, tempCell);
			}
		}
	}
}

void GameScene::draw()
{
	AppWindow& window = AppWindow::getInstance();
	
	window.clear();

	renderer.begin();

	// Draw the tile map
	renderer.draw(*cMap);

	renderer.end();
	
	window.display();
}
