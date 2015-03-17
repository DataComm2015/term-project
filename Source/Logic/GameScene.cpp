#include "GameScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

sf::IntRect runFrames[8];
Animation *runAnim;

GameScene::GameScene() : renderer(AppWindow::getInstance(), 4000)
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
	v = new Vessel(WARRIOR,NULL,0,0);

	// Load the tileset
	tilemap = Manager::TileManager::load("Logic/Environment/map.tset");
	championSprite = Manager::TextureManager::store(
			Manager::TextureManager::load("Multimedia/Assets/Art/Player/Run/Body/vessel-run-sheet-right.png")
			);

	// an example, obviously...
	runAnim = new Animation(&championSGO, sf::Vector2i(32, 32), 8, 7);
	
	cMap->setTexture(tilemap);
	championSGO().setTexture(*Manager::TextureManager::get(championSprite));
	championSGO().setTextureRect(sf::IntRect(0, 0, 32, 32));
	championSGO().setScale(2, 2);
	championSGO.middleAnchorPoint(true);
	
	// Generate the game map
	if (!gMap->generateMap())
	{
		cerr << "Invalid map dimensions." << endl;
	}

	generateWater();

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

	for (int i = 0; i < waterMap->getHeight(); i++)
	{
		for (int j = 0; j < waterMap->getWidth(); j++)
		{
			delete waterMap->getCell(j, i);
		}
	}

	delete cMap;
	delete waterMap;
}

void GameScene::update(sf::Time t)
{
	//printf("Update Run Scene\n");
	//championSGO().setPosition(viewMain.getCenter());

	//viewMain.move(v->getXSpeed(), v->getYSpeed());
	v->move();
	
	if(v->getXSpeed() != 0 || v->getYSpeed() != 0)
		runAnim->run(true);
	else
		runAnim->pause(true);
	
	//flip the sprite if facing left
	if(v->getDirection() == 0)
		championSGO().setScale(-2, 2);
	else
		championSGO().setScale(2, 2);
	
	//the 20 is to offset the size of the sprite, since it scales around the left hand of the sprite... pretty hackey but only temporary. ask lewis if you don't get it
	championSGO().setPosition(v->getXPosition(), v->getYPosition());
	
	runAnim->update(t);
	
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
		v->detectMove();
		
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
	else if( e.type == sf::Event::KeyReleased )
	{
		v->stop(e.key.code);
	}
}

void GameScene::draw()
{
	// Increment the wave phase
	phase += WAVE_PHASE_CHANGE;
	
	AppWindow& window = AppWindow::getInstance();
	
	window.clear();

	window.setView(viewMain);

	renderer.begin();

	waveShader.setParameter("wave_phase", phase);

	// Draw the tile map
	renderer.draw(*waterMap, &waveShader);
	renderer.draw(*cMap);

	renderer.end();

	renderer.begin();
	renderer.draw(championSGO);
	renderer.end();
	
	window.display();
}


void GameScene::generateWater()
{
	// Setup the wave shader
	phase = 0.0;
	waveShader.loadFromFile("Multimedia/Assets/Shaders/wave.vert", sf::Shader::Vertex);
	waveShader.setParameter("wave_amplitude", sf::Vector2f(WAVE_X, WAVE_Y));
	waveShader.setParameter("wave_phase", phase);

	// Create the water map
	waterMap = new Map(cMap->getWidth() + WATER_BUFFER, cMap->getHeight() + WATER_BUFFER);

	// Set the water map tiles
	int randomWater;
	vector<CellTile> waterTiles({WATER_1, WATER_2});

	for (int i = 0; i < waterMap->getHeight(); i++)
	{
		for (int j = 0; j < waterMap->getWidth(); j++)
		{
			Cell *tempCell = new Cell();

			randomWater = rand() % 2;

			tempCell->setTileId(waterTiles[randomWater]);

			waterMap->setCell(j, i, tempCell);
		}
	}

	// Set the water map texture
	waterMap->setTexture(tilemap);

	// Re-adjust the water map location

}
