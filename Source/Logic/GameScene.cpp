#include "GameScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

Animation *runAnim;
Animation *runAnim_mask;
Animation *runAnim_wep;

void onclick()
{
	static int i = 0;

	if(i > 6)
		exit(0);
		
	i++;
}

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
	maskSprite = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/Art/Player/Run/Masks/vessel-run-sheet-mask01-right.png"));
	wepSprite = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/Art/Player/Run/Weapons/staff-run-sheet-right.png"));
	butSprite = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
	
	// an example, obviously...
	runAnim = new Animation(&championSGO, sf::Vector2i(32, 32), 8, 7);
	runAnim_mask = new Animation(&maskSGO, sf::Vector2i(32,32),8,7);
	runAnim_wep = new Animation(&wepSGO, sf::Vector2i(32,32),8,7);
	
	cMap->setTexture(tilemap);
	championSGO().setTexture(*Manager::TextureManager::get(championSprite));
	championSGO().setTextureRect(sf::IntRect(0, 0, 32, 32));
	championSGO().setScale(2, 2);
	championSGO.middleAnchorPoint(true);
	
	maskSGO().setTexture(*Manager::TextureManager::get(maskSprite));
	maskSGO().setTextureRect(sf::IntRect(0,0,32,32));
	maskSGO().setScale(2,2);
	maskSGO.middleAnchorPoint(true);
	
	wepSGO().setTexture(*Manager::TextureManager::get(wepSprite));
	wepSGO().setTextureRect(sf::IntRect(0,0,32,32));
	wepSGO().setScale(2,2);
	wepSGO.middleAnchorPoint(true);
	
	sf::Font *arial = new sf::Font();
	arial->loadFromFile("Multimedia/Assets/Fonts/arial.ttf");
	
	b1 = new GUI::Button(&championSGO, *Manager::TextureManager::get(butSprite), sf::Vector2f(200, 200), onclick);
	tb = new GUI::TextBox(NULL);
	tb->toggleSelected(true);
	tb->operator()().setFont(*arial);
	
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
	{
		runAnim->run(true);
		runAnim_mask->run(true);
		runAnim_wep->run(true);
	}
	else
	{
		runAnim->pause(true);
		runAnim_mask->pause(true);
		runAnim_wep->pause(true);
		runAnim->step(0);
		runAnim_mask->step(0);
		runAnim_wep->step(0);
	}
	
	//flip the sprite if facing left
	if(v->getDirection() == 0)
	{
		championSGO().setScale(-2, 2);
		maskSGO().setScale(-2,2);
		wepSGO().setScale(-2,2);
		b1->toggleEnabled(true);
	}
	else
	{
		championSGO().setScale(2, 2);
		maskSGO().setScale(2,2);
		wepSGO().setScale(2,2);
		b1->toggleEnabled(false);
	}
	
	championSGO().setPosition(v->getXPosition(), v->getYPosition());
	maskSGO().setPosition(v->getXPosition(), v->getYPosition());
	wepSGO().setPosition(v->getXPosition(), v->getYPosition());
	
	runAnim->update(t);
	runAnim_mask->update(t);
	runAnim_wep->update(t);
	
	
	b1->update(t);
	
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
			case sf::Keyboard::Return:
			{
				break;
			}
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
	
	tb->process(e);
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
	renderer.draw(*b1);
	renderer.draw(*tb);
	renderer.draw(championSGO);
	renderer.draw(maskSGO);
	renderer.draw(wepSGO);
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
