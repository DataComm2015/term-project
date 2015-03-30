#include "GameScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;
/*
//Do not delete, we might use this later in vessel.cpp - Sebastian + Eric
Animation *runAnim;
Animation *runAnim_mask;
Animation *runAnim_wep;
*/

void onclick()
{
	static int i = 0;

	if (i > 6)
		exit(0);

	i++;
}

GUI::HealthBar *pubHB;
void onclickHealthTest()
{
	static float health = 1.0;
	
	health = health - .10;
	
	if(health >= 0)
		pubHB->update(health);
}



void updateMainView(sf::View& v)
{
	v = AppWindow::getInstance().getCurrentView();
	v.zoom(0.66);
}

GameScene::GameScene() : renderer(AppWindow::getInstance(), 48400)
{
	// Create the maps
	std::cout << "creating map " << std::endl;
	cMap = new Map(90, 90);
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
	waterMap = new Map(cMap->getWidth() + WATER_BUFFER, cMap->getHeight() + WATER_BUFFER);

	/* THIS IS TO SHOW HOW TO MOVE / CREATE ENTITIES / PROJECTILES. PLEASE REMOVE WHEN PROPERLY IMPLEMENTED */
	/* SIDE NOTE PROJECTILES SHOULD NOT GET CREATED LIKE THIS THEY SHOULD BE CREATED VIA THE PROJECTILE MANAGER */

	/*std::cout << "Entity / Projectile move example (GameScene.cpp)" << std::endl;

 p = new Projectile(cMap, 10, 10, NULL, 1, 1);
	//				   map, x, y, controller, height, width
	Projectile p2 = Projectile(cMap, 20, 20, NULL, 1, 1);

	std::cout << "projectile 1 " << p << std::endl;
	std::cout << "projectile 2 " << &p2 << std::endl;

	// move the second projectile to collide with the first.
	std::cout << "Projectile 2 hit: " << p2.move(10, 10, false) << std::endl;
	// Entities all extend sf::Rect so you can get their x, y by checking the top left.
	// As a side note, both entities and cells are FloatRects so are view ports intersect can be used to
	// see if an entity or cell should be visible on the map.
	// this should be useful for figuring out what needs to be rendered down the road.
	std::cout << "Projectile 1 hit: " << p->move(p->top + 10, p->left + 10, false) << std::endl;
	std::cout << "Projectile 1 hit: " << p->move(p->top + 20, p->left + 10, false) << std::endl;
	std::cout << "Projectile 2 hit: " << p2.move(10, 10, false) << std::endl;

	delete p;
*/
	/* END SAMPLE CREATION */

	std::cout << "making tileset" << std::endl;
	// Load the tileset
	tilemap = Manager::TileManager::load("Assets/Tiles/map.tset");
	championSprite = Manager::TextureManager::store(
		Manager::TextureManager::load("Assets/Art/Player/Run/Body/vessel-run-sheet.png")
		);
	maskSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Player/Run/Masks/vessel-run-mask01-sheet.png"));
	wepSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Player/Run/Weapons/staff-run-sheet.png"));
	butSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/button.png"));
	scat_music = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Sound/music.ogg"));
	chick_sound = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/sound.wav"));
	placeholderSprite = Manager::TextureManager::store(
		Manager::TextureManager::load("Assets/Art/Misc/placeholder_32.png")
		);

	// an example, obviously...
	/*
	v = new Vessel(SHAMAN, nullptr, 0, 0);

	runAnim = new Animation(&championSGO, sf::Vector2i(32, 32), 8, 7);
	runAnim_mask = new Animation(&maskSGO, sf::Vector2i(32, 32), 8, 7);
	runAnim_wep = new Animation(&wepSGO, sf::Vector2i(32, 32), 8, 7);
	*/

	cMap->setTexture(tilemap);
	championSGO.sprite().setTexture(*Manager::TextureManager::get(championSprite));
	championSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	championSGO.sprite().setScale(2, 2);
	championSGO.middleAnchorPoint(true);

	maskSGO.sprite().setTexture(*Manager::TextureManager::get(maskSprite));
	maskSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	maskSGO.sprite().setScale(2, 2);
	maskSGO.middleAnchorPoint(true);

	wepSGO.sprite().setTexture(*Manager::TextureManager::get(wepSprite));
	wepSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	wepSGO.sprite().setScale(2, 2);
	wepSGO.middleAnchorPoint(true);

	placeHolderSGO.sprite().setTexture(*Manager::TextureManager::get(placeholderSprite));
	placeHolderSGO.sprite().setScale(1, 1);

	s = new TheSpinner(placeHolderSGO, cMap, 25, 25, 5, 1);
	s2 = new TheSpinner(placeHolderSGO, cMap, 25, 35, 5, -1);

	std::cout << "before vesesl made" << std::endl;
	vessel = new Vessel(championSGO, cMap, 45.0F, 45.0F, NULL, 1.0F, 1.0F);


	sf::Font *arial = new sf::Font();
	arial->loadFromFile("Assets/Fonts/arial.ttf");

	tb = new GUI::TextBox(nullptr, nullptr);
	tb->text().setScale(0.5, 0.5);
	tb->text().move(0, -5);
	tb->toggleSelected(true);
	tb->text().setFont(*arial);

	Manager::MusicManager::get(scat_music)->setVolume(60);
	Manager::MusicManager::get(scat_music)->play();

	// Link game objects (not everything is linked, for example purposes only)
	// as of now, the hierarchy system is barely used in this example
	maskSGO.add(*tb);

	// Generate stuff

	// center the cell map
	std::cout << "centering map" << std::endl;
	cMap->trans.translate(cMap->getWidth() * 0.5f * -32, cMap->getHeight() * 0.5f * -32);

	if (!gMap->generateMap(0))
	{
		cerr << "Invalid map dimensions." << endl;
	}
	std::cout << "before generate water" << std::endl;
	generateWater();
	std::cout << "after generate water" << std::endl;
	generateUI();
	std::cout << "after generate ui" << std::endl;
}

void GameScene::onLoad()
{
	// update views
	updateMainView(viewMain);
	viewUI = AppWindow::getInstance().getCurrentView();

	// position buttons
	positionButtons();

	// Enable buttons
	b1->toggleEnabled(true);
	b2->toggleEnabled(true);
	b3->toggleEnabled(true);
	b4->toggleEnabled(true);
	b5->toggleEnabled(true);
	b6->toggleEnabled(true);
}

void GameScene::positionButtons()
{
	// Get Window size
	sf::Vector2u windowSize = AppWindow::getInstance().getSize();

	// Get button image height
	unsigned int height = Manager::TextureManager::get(butSprite)->getSize().y;

	// Scale button to 10 percent of the window height
	float buttonScale = 0.10*windowSize.y/height;
	b1->sprite().setScale(buttonScale, buttonScale);
	b2->sprite().setScale(buttonScale, buttonScale);
	b3->sprite().setScale(buttonScale, buttonScale);
	b4->sprite().setScale(buttonScale, buttonScale);
	b5->sprite().setScale(buttonScale, buttonScale);
	b6->sprite().setScale(buttonScale, buttonScale);

	// position scaled buttons
	float buttonWidth = b1->sprite().getGlobalBounds().width;
	float buttonHeight = b1->sprite().getGlobalBounds().height;

	b1->sprite().setPosition((windowSize.x / 2.0) - (buttonWidth * 3), windowSize.y - 1.25*buttonHeight);
	b2->sprite().setPosition((windowSize.x / 2.0) - (buttonWidth * 2), windowSize.y - 1.25*buttonHeight);
	b3->sprite().setPosition((windowSize.x / 2.0) - (buttonWidth), windowSize.y - 1.25*buttonHeight);
	b4->sprite().setPosition((windowSize.x / 2.0), windowSize.y - 1.25*buttonHeight);
	b5->sprite().setPosition((windowSize.x / 2.0) + (buttonWidth), windowSize.y - 1.25*buttonHeight);
	b6->sprite().setPosition((windowSize.x / 2.0) + (buttonWidth * 2), windowSize.y - 1.25*buttonHeight);
	
	// position healthbar
	hb->sprite().setPosition((windowSize.x / 2.0), windowSize.y - 4*buttonHeight);
}

void GameScene::unLoad()
{
	b1->toggleEnabled(false);
	b2->toggleEnabled(false);
	b3->toggleEnabled(false);
	b4->toggleEnabled(false);
	b5->toggleEnabled(false);
	b6->toggleEnabled(false);
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
	auto entities = cMap->getEntities();
	for ( auto it = entities.begin(); it != entities.end(); ++it)
	{
		/*we have to break out one iterator early because the last iterator
		  was in a REALLY WIERD memory address and was causing bad_alloc()
		  exceptions to be thrown. This solution is really janky and should
		  probably be investigated further once the game is running.
			- Eric & Sebastian*/
		if(it != --entities.end())
		{
		    (*it)->onUpdate();
		}
	}
	//Do not delete, we might use this later in vessel.cpp - Sebastian + Eric

	/*
	v->move();


	if (v->getXSpeed() != 0 || v->getYSpeed() != 0)
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
	if (v->getDirection() == 0)
	{
		championSGO.sprite().setScale(-2, 2);
		maskSGO.sprite().setScale(-2, 2);
		wepSGO.sprite().setScale(-2, 2);
		//b1->toggleEnabled(true);
	}
	else
	{
		championSGO.sprite().setScale(2, 2);
		maskSGO.sprite().setScale(2, 2);
		wepSGO.sprite().setScale(2, 2);
		//b1->toggleEnabled(false);
	}
	*/

	sf::Listener::setPosition(viewMain.getCenter().x-45, viewMain.getCenter().y-45, 0);

	//Do not delete, we might use this later in vessel.cpp - Sebastian + Eric
	/*
	championSGO.sprite().setPosition(v->getXPosition(), v->getYPosition());
	maskSGO.sprite().setPosition(v->getXPosition(), v->getYPosition());
	wepSGO.sprite().setPosition(v->getXPosition(), v->getYPosition());

	runAnim->update(t);
	runAnim_mask->update(t);
	runAnim_wep->update(t);
	*/

	s2->update(t);
	s->update(t);

	// Update buttons
	b1->update(t);
	b2->update(t);
	b3->update(t);
	b4->update(t);
	b5->update(t);
	b6->update(t);

//	cMap->setPosition(cMap->getWidth() * 0.5f * -32, cMap->getHeight() * 0.5f * -32);
	//waterMap->setPosition(waterMap->getWidth() * 0.5f * -32, waterMap->getHeight() * 0.5f * -32);

	viewMain.setCenter(
		vessel->getGlobalTransform().transformPoint(vessel->getXPosition()*32.0F, vessel->getYPosition()*32.0F));

	// Increment the wave phase
	phase += WAVE_PHASE_CHANGE;
	waveShader.setParameter("wave_phase", phase);
}

void GameScene::processEvents(sf::Event& e)
{
	if (e.type == sf::Event::Closed)
	{
        ((ClientMux*)NetworkEntityMultiplexer::getInstance())->shutdown();
		AppWindow::getInstance().close();

		AppWindow::getInstance().close();
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		for (auto l = keyListeners.begin(); l != keyListeners.end(); ++l)
		{
			(*l)->onKeyPressed(e.key.code);
		}

		// ALL OF THE FOLLOWING IS TEMPORARY
		switch (e.key.code)
		{
		    case sf::Keyboard::Return:
		    {
			    break;
		    }
		}
	}
	else if (e.type == sf::Event::KeyReleased)
	{
		for (auto l = keyListeners.begin(); l != keyListeners.end(); ++l)
		{
			(*l)->onKeyReleased(e.key.code);
		}

		// v->stop(e.key.code);
	}
	else if (e.type == sf::Event::Resized)
	{
		// update views
		updateMainView(viewMain);
		viewUI = AppWindow::getInstance().getCurrentView();
		positionButtons();
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			current = Manager::SoundManager::play(chick_sound, AppWindow::getInstance().getMousePositionRelativeToWindowAndView(viewMain));
			current.play();
		}
	}

	tb->process(e);
}

void GameScene::draw()
{
	AppWindow& window = AppWindow::getInstance();

	window.clear();

	window.setView(viewMain);

	renderer.begin();

	// Draw the maps
	renderer.states.shader = &waveShader;
	renderer.draw(waterMap);
	renderer.states.shader = nullptr;
	renderer.draw(cMap, true);

	renderer.end();

	renderer.begin();

	// draw the objects
	//renderer.draw(championSGO2);
	renderer.draw(&maskSGO, true);
	renderer.draw(wepSGO);

	renderer.end();

	// Draw UI
	window.setView(viewUI);

	renderer.begin();

	renderer.draw(b1);
	renderer.draw(b2);
	renderer.draw(b3);
	renderer.draw(b4);
	renderer.draw(b5);
	renderer.draw(b6);
	renderer.draw(hb);

	renderer.end();

	window.display();
}

void GameScene::addKeyListener(KeyListener* listener)
{
	keyListeners.insert(listener);
}

void GameScene::rmKeyListener(KeyListener* listener)
{
	keyListeners.erase(listener);
}

void GameScene::generateMap(int seed)
{
    gMap->generateMap(seed);
}

void GameScene::generateWater()
{
	// Setup the wave shader
	phase = 0.0;
	waveShader.loadFromFile("Assets/Shaders/wave.vert", sf::Shader::Vertex);
	waveShader.setParameter("wave_amplitude", sf::Vector2f(WAVE_X, WAVE_Y));
	waveShader.setParameter("wave_phase", phase);

	// Set the water map tiles
	int randomWater;
	vector<CellTile> waterTiles({ WATER_1, WATER_2 });

	for (int i = 0; i < waterMap->getHeight(); i++)
	{
		for (int j = 0; j < waterMap->getWidth(); j++)
		{
			Cell* oldCell = waterMap->getCell(j, i);
			if (oldCell) delete oldCell;

			Cell *tempCell = new Cell();

			randomWater = rand() % 2;

			tempCell->setTileId(waterTiles[randomWater]);

			waterMap->setCell(j, i, tempCell);
		}
	}

	// Set the water map texture
	waterMap->setTexture(tilemap);

	// Center the map
	waterMap->trans = sf::Transform::Identity;
	waterMap->trans.translate(waterMap->getWidth() * 0.5f * -32, waterMap->getHeight() * 0.5f * -32);
}

void GameScene::generateUI()
{
	// Create buttons
	butSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/button.png"));
	healthSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/HUDhealthbar.png"));

	sf::Vector2u imageSize = Manager::TextureManager::get(butSprite)->getSize();
	unsigned int width = imageSize.x / 4;
	unsigned int height = imageSize.y;

	sf::Vector2f butSize = sf::Vector2f(width, height);

	b1 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
	b2 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
	b3 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
	b4 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
	b5 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
	b6 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclickHealthTest);
	
	// Create health bar (If statement here if vessel or deity)
	imageSize = Manager::TextureManager::get(healthSprite)->getSize();
	width = imageSize.x;
	height = imageSize.y;

	sf::Vector2f healthSize = sf::Vector2f(width, height);

	hb = new GUI::HealthBar(*Manager::TextureManager::get(healthSprite), healthSize, viewUI);
	
	pubHB = hb;
}
