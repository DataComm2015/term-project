#include "GameScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

GameScene::GameScene() : renderer(AppWindow::getInstance(), 4000)
{
	// Create the cell map
	cMap = new Map(25, 25);
	//waterMap = new Map(20, 20);

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

	// Load the tileset
	tilemap = Manager::TileManager::load("Logic/Environment/map.tset");

	cMap->setTexture(tilemap);

	// Generate the game map
	if (!gMap->generateMap())
	{
		cerr << "Invalid map dimensions." << endl;
	}

	/*
	// Set the water map tiles
	for (int i = 0; i < waterMap->getHeight(); i++)
	{
		for (int j = 0; j < waterMap->getWidth(); i++)
		{
			Cell *tempCell = new Cell();
			tempCell->setTileId(31);

			waterMap->setCell(j, i, tempCell);
		}
	}

	//watermap = Manager::TileManager::load("Logic/Environment/map.tset");
	waterMap->setTexture(tilemap);
	*/

	// Set the active view
	AppWindow& window = AppWindow::getInstance();
	viewMain = window.getView();
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

	/*
	for (int i = 0; i < waterMap->getHeight(); i++)
	{
		for (int j = 0; j < waterMap->getWidth(); j++)
		{
			delete waterMap->getCell(j, i);
		}
	}
	*/

	delete cMap;
	//delete waterMap;
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
		// ALL OF THE FOLLOWING IS TEMPORARY
		switch(e.key.code)
		{
			case sf::Keyboard::Left:
			{
				viewMain.move(-5, 0);
				break;
			}

			case sf::Keyboard::Right:
			{
				viewMain.move(5, 0);
				break;
			}

			case sf::Keyboard::Up:
			{
				viewMain.move(0, -5);
				break;
			}

			case sf::Keyboard::Down:
			{
				viewMain.move(0, 5);
				break;
			}

			case sf::Keyboard::Dash:
			{
				viewMain.zoom(1.1);
				break;
			}

			case sf::Keyboard::Equal:
			{
				viewMain.zoom(0.9);
				break;
			}

			case sf::Keyboard::Space:
			{
				// Generate the game map
				gMap->generateMap();

				break;
			}
		}
	}
}

void GameScene::draw()
{
	AppWindow& window = AppWindow::getInstance();
	
	window.clear();

	window.setView(viewMain);

	renderer.begin();

	// Draw the tile map
	//renderer.draw(*waterMap);
	renderer.draw(*cMap);

	renderer.end();
	
	window.display();
}
