/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: GameScene.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--
-- DATE: March 10, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Chris Klassen
--
-- PROGRAMMER:  Chris Klassen
--
-- NOTES:
--        This file contains the implementation of the client game scene.
--		  This scene handles all in-game client logic.
----------------------------------------------------------------------------------------------------------------------*/


#include "GameScene.h"
#include "Entities/CommandEntity.h"
#include "PlayerLobbyChoices.h"
#include "Skills.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

id_resource GameScene::tilemap = Manager::TileManager::load("Assets/Tiles/map.tset");
id_resource GameScene::butSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));
id_resource GameScene::demiseBtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/demise-btn.png"));
id_resource GameScene::vitalityBtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/vitality-btn.png"));
id_resource GameScene::warriorBtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-btn.png"));
id_resource GameScene::shamanBtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));
id_resource GameScene::buffskillbtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/buff-skill-btn.png"));
id_resource GameScene::healskillbtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/heal-skill-btn.png"));
id_resource GameScene::healingcircleskillbtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/healingcircle-skill-btn.png"));
id_resource GameScene::debuffskillbtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/debuff-skill-btn.png"));
id_resource GameScene::hurtskillbtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/hurt-skill-btn.png"));
id_resource GameScene::summonskillbtn = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/summon-skill-btn.png"));
id_resource GameScene::hbarSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/HUDhealthbar.png"));
id_resource GameScene::hbgSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/HUDbase.png"));
id_resource GameScene::crosshairImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Deity/crosshair.png"));

id_resource GameScene::deityRNGImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Deity/deity-ring.png"));
id_resource GameScene::deityBUFImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Deity/deitycircle-buff.png"));
id_resource GameScene::deityDMGImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Deity/deitycircle-debuff.png"));
id_resource GameScene::deityDBFImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Deity/deitycircle-damage.png"));
id_resource GameScene::deityHLGImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Deity/deitycircle-healing.png"));

id_resource GameScene::game_msc = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Music/music_gameplay.ogg"));
id_resource GameScene::ambience_msc = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Sound/Environment/ambient_01.ogg"));

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onclick()
{
	static int i = 0;

	if (i > 6)
		exit(0);

	i++;
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onclickLevelup()
{
	static int level = 1;
	std::string slevel;

	// level should be double digits
	if(level < 10)
		slevel = "0" + std::to_string(level++);
	else
		slevel = std::to_string(level++);
    //pubLevelInd->setText(slevel);
}


/******************************************************************************
*	FUNCTION: GameScene
*
*	DATE: March 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: GameScene()
*
*	PARAMETERS:
*
*	RETURNS: nothing
*
*	NOTES:
*		This is the constructor for the game scene. It creates all maps and
*		sets up needed resources.
******************************************************************************/
GameScene::GameScene() : renderer(AppWindow::getInstance(), 48400)
{
	// Create the maps
	std::cout << "creating map " << std::endl;
	cMap = new Map(90, 90);
	myMap = cMap;
	for (int i = 0; i < cMap->getHeight(); i++)
	{
		for (int j = 0; j < cMap->getWidth(); j++)
		{
			Cell *tempCell = new Cell(j, i);
			tempCell->setTileId(1);

			cMap->setCell(j, i, tempCell);
		}
	}
	gMap = new GameMap(cMap);
	waterMap = new Map(cMap->getWidth() + WATER_BUFFER, cMap->getHeight() + WATER_BUFFER);

	myVessel = NULL;

	butSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/button.png"));

	cMap->setTexture(tilemap);

	// Generate stuff

	if (!gMap->generateMap(0))
	{
		cerr << "Invalid map dimensions." << endl;
	}
	std::cout << "before generate water" << std::endl;
	generateWater();
	std::cout << "after generate water" << std::endl;

	music = Manager::MusicManager::get(GameScene::game_msc);
	ambience = Manager::MusicManager::get(GameScene::ambience_msc);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::onLoad()
{
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	characterType = cm->getCommandEntity()->getPlayerMode();
	switch (characterType)
	{
		case PLAYER_MODE::VESSEL:
			classType = cm->getCommandEntity()->getLobbyOption()->vesselChoice;
			break;
		case PLAYER_MODE::DEITY:
			classType = cm->getCommandEntity()->getLobbyOption()->deityChoice;
			break;
	}

	printf("characterType: %d, classType: %d\n",characterType,classType);

	// update views
	viewMain = viewUI = viewMinimap = AppWindow::getInstance().getCurrentView();
	viewMain.zoom(0.33);

	// minimap view
	viewMinimap.setViewport(sf::FloatRect(0.76f,0.01f,0.23f,0.23f));
	viewMinimap.zoom(2.f);
	minimapBorder.setFillColor(sf::Color::Black);
	minimapBorder.setOutlineThickness(5); //thickness set to 5 pixels

	// position buttons
	generateUI();
	positionUI();

	// Enable buttons
	b1->toggleEnabled(true);
	b2->toggleEnabled(true);
	b3->toggleEnabled(true);

	music->setVolume(60);
	music->play();
	ambience->setVolume(40);
	ambience->play();
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::positionUI()
{
	// Get Window size
	sf::Vector2u windowSize = AppWindow::getInstance().getSize();

	// Get button image height
	unsigned int height = Manager::TextureManager::get(butSprite)->getSize().y;

	// Scale button to 10 percent of the window height
	float buttonScale = 0.50*windowSize.y/height;
	b1->sprite().setScale(buttonScale, buttonScale);
	b2->sprite().setScale(buttonScale, buttonScale);
	b3->sprite().setScale(buttonScale, buttonScale);

	// position scaled buttons
	float buttonWidth = b1->sprite().getGlobalBounds().width;
	float buttonHeight = b1->sprite().getGlobalBounds().height;

	b1->sprite().setPosition((windowSize.x / 2.0) - (buttonWidth), windowSize.y - 3*buttonHeight);
	b2->sprite().setPosition((windowSize.x / 2.0), windowSize.y - 3*buttonHeight);
	b3->sprite().setPosition((windowSize.x / 2.0) + (buttonWidth), windowSize.y - 3*buttonHeight);

	// Scale healthbar
	hb->sprite().setScale(3, 3);

	// position healthbar
	hb->sprite().setPosition(20, 20);

	//the border for the minimap
	minimapBorder.setSize(
		sf::Vector2f(viewMinimap.getViewport().width*windowSize.x,
			     viewMinimap.getViewport().height*windowSize.y));
	minimapBorder.setPosition(
		sf::Vector2f(viewMinimap.getViewport().left*windowSize.x,
		  	     viewMinimap.getViewport().top*windowSize.y));
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::setPlayerVessel(Vessel *vessel)
{
	myVessel = vessel;
	myVessel->setHealthBar(hb);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::stopAllSounds()
{
    auto entities = cMap->getEntities();
	for ( auto it = entities.begin(); it != entities.end(); ++it)
	{
        Creature *creature = dynamic_cast<Creature*>((*it));
        if (creature)
            creature->stopAllSounds();
	}
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::unLoad()
{
	b1->toggleEnabled(false);
	b2->toggleEnabled(false);
	b3->toggleEnabled(false);

	music->stop();
	ambience->stop();
}


/******************************************************************************
*	FUNCTION: ~GameScene
*
*	DATE: March 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: ~GameScene();
*
*	PARAMETERS:
*
*	RETURNS: nothing
*
*	NOTES:
*		This destructor cleans up the maps used in the game scene.
******************************************************************************/
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


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER: Melvin Loho, Sanders Lee
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::update(sf::Time t)
{
	checkBtns(t);
	// static int listEntity = 100;
	auto entities = cMap->getEntities();
	for ( auto it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->onUpdate(t.asSeconds());
	}

	if (myVessel != NULL)
	{
		//myVessel->getSprite().sprite().rotate(1);

		viewMain.setCenter(myVessel->getGlobalTransform().transformPoint(16,16));
		viewMinimap.setCenter(myVessel->getGlobalTransform().transformPoint(16,16));
        sf::Listener::setPosition(myVessel->left, myVessel->top, 0);
	}
	else
	{
		crossHairSGO->sprite().rotate(1);
	}

	/*
	sf::Vector2f mousePos = AppWindow::getInstance().getMousePositionRelativeToWindowAndView(viewMain);
	std::cout << "mouse : " << mousePos.x << ", " << mousePos.y << std::endl;
	cout << "vessel:   " << myVessel->left << ", " << myVessel->top << endl;
	cout << "viewmain: " << viewMain.getCenter().x << ", " << viewMain.getCenter().y << endl;
	*/

	// listEntity = false;
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

	//Do not delete, we might use this later in vessel.cpp - Sebastian + Eric
	/*
	championSGO.sprite().setPosition(v->getXPosition(), v->getYPosition());
	maskSGO.sprite().setPosition(v->getXPosition(), v->getYPosition());
	wepSGO.sprite().setPosition(v->getXPosition(), v->getYPosition());

	runAnim->update(t);
	runAnim_mask->update(t);
	runAnim_wep->update(t);
	*/
	updateSkillGraphics(t);

	// Update buttons
	b1->update(t);
	b2->update(t);
	b3->update(t);

	// Increment the wave phase
	phase += WAVE_PHASE_CHANGE;
	waveShader.setParameter("wave_phase", phase);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::processEvents(sf::Event& e)
{
	static std::set<int> depressedKeys;
	Scene::processEvents(e);
	if (e.type == sf::Event::Closed)
	{
        ((ClientMux*)NetworkEntityMultiplexer::getInstance())->shutdown();
		AppWindow::getInstance().close();
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		if(characterType == PLAYER_MODE::VESSEL)
		{
			if (depressedKeys.find((int)e.key.code) == depressedKeys.end())
			{
				depressedKeys.insert((int)e.key.code);
				for (auto l = keyListeners.begin(); l != keyListeners.end(); ++l)
				{
					(*l)->onKeyPressed(e.key.code);
				}
			}
		}
		else
		{
			float camSpeed = 15;
			switch (e.key.code)
			{
				case sf::Keyboard::Left:
				{
					viewMain.setCenter(viewMain.getCenter().x - camSpeed, viewMain.getCenter().y);
					vm = viewMain;
					break;
				}
				case sf::Keyboard::Right:
				{
					viewMain.setCenter(viewMain.getCenter().x + camSpeed, viewMain.getCenter().y);
					vm = viewMain;
					break;
				}
				case sf::Keyboard::Up:
				{
					viewMain.setCenter(viewMain.getCenter().x, viewMain.getCenter().y - camSpeed);
					vm = viewMain;
					break;
				}
				case sf::Keyboard::Down:
				{
					viewMain.setCenter(viewMain.getCenter().x, viewMain.getCenter().y + camSpeed);
					vm = viewMain;
					break;
				}
				case sf::Keyboard::Return:
				{
					break;
				}
			}
			viewMinimap.setCenter(viewMain.getCenter().x, viewMain.getCenter().y);
		}
	}
	else if (e.type == sf::Event::KeyReleased)
	{
		for (auto l = keyListeners.begin(); l != keyListeners.end(); ++l)
		{
			(*l)->onKeyReleased(e.key.code);
		}
		depressedKeys.erase((int)e.key.code);

		// v->stop(e.key.code);
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if(characterType == PLAYER_MODE::VESSEL)
		{
			sf::Vector2f mouse = AppWindow::getInstance().getMousePositionRelativeToWindowAndView(viewMain);
			sf::Vector2f viewVector = viewMain.getCenter();
			
			/*viewVector.x = convertX(viewVector.x);
			viewVector.y = convertY(viewVector.y);
			*/std::cout << "Mouse clicked: " << mouse.x << " " << mouse.y << std::endl;
			std::cout << "ViewMain centre: " << viewVector.x << " " << viewVector.y << std::endl;

			for (auto l = clickListeners.begin(); l != clickListeners.end(); ++l)
			{
				(*l)->onMouseClick(e.mouseButton.button, ((NetworkEntity*)myVessel->getController())->getId(),
									ActionType::normalAttack, viewVector.x - (float)mouse.x, viewVector.y - (float)mouse.y);
				//current = Manager::SoundManager::play(chick_sound, AppWindow::getInstance().getMousePositionRelativeToWindowAndView(viewMain));
				//current.play();
			}
		}
	}
}


/******************************************************************************
*	FUNCTION: draw
*
*	DATE: March 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: draw();
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
*		This function draws the elements of the game to the window.
******************************************************************************/
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
	renderer.draw(cMap);

	renderer.end();

	// Draw UI
	window.setView(viewUI);

	renderer.begin();

	if(characterType == PLAYER_MODE::DEITY)
	{
		renderer.draw(b1);
		renderer.draw(b2);
		renderer.draw(b3);
		renderer.draw(crossHairSGO);
	}
	else if(characterType == PLAYER_MODE::VESSEL)
	{
		renderer.draw(hb);
	}

	renderer.end();

	window.draw(minimapBorder);

	//draw the minimap
	window.setView(viewMinimap);

	renderer.begin();

	renderer.states.shader = &waveShader;
	renderer.draw(waterMap);
	renderer.states.shader = nullptr;
	renderer.draw(cMap);

	renderer.end();

	window.display();
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
  SKILLTYPE st;

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::rmKeyListener(KeyListener* listener)
{
	keyListeners.erase(listener);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::addClickListener(ClickListener* listener)
{
	clickListeners.insert(listener);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::rmClickListener(ClickListener* listener)
{
	clickListeners.erase(listener);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::generateMap(int seed)
{
    gMap->generateMap(seed);
}


/******************************************************************************
*	FUNCTION: generateWater
*
*	DATE: March 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*				Lewis Scott
*
*	INTERFACE: generateWater
*
*	PARAMETERS:
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function generates the water map, assigns it specific tiles,
*		and applies a water shader to it.
******************************************************************************/
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

	// Set the water cliff tiles
	vector<CellTile> waterCliffTiles({ WATER_C1, WATER_C2 });

	int vWaterOffset = waterMap->getHeight() - (WATER_BUFFER / 2);
	int hWaterOffset = (WATER_BUFFER / 2) + 1;

	// Buffer cliff tiles so it doesn't look weird
	for (int i = 0; i < gMap->getWidth() - 2; i++)
	{
		randomWater = rand() % 2;
		waterMap->getCell(hWaterOffset + i, vWaterOffset - 1)->setTileId(GRASS_C1);
	}

	// Actual water cliff tiles
	for (int i = 0; i < gMap->getWidth() - 2; i++)
	{
		randomWater = rand() % 2;
		waterMap->getCell(hWaterOffset + i, vWaterOffset)->setTileId(waterCliffTiles[randomWater]);
	}

	waterMap->getCell(hWaterOffset, vWaterOffset)->setTileId(WATER_CL);
	waterMap->getCell(hWaterOffset + gMap->getWidth() - 3, vWaterOffset)->setTileId(WATER_CR);


	// Set the water map texture
	waterMap->setTexture(tilemap);

	// Center the map
	waterMap->trans = sf::Transform::Identity;
	waterMap->trans.translate(waterMap->getWidth() * 0.5f * -32, waterMap->getHeight() * 0.5f * -32);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER: Jeff Bayntun
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::generateUI()
{
	sf::Vector2u imageSize = Manager::TextureManager::get(butSprite)->getSize();
	unsigned int width = imageSize.x / 4;
	unsigned int height = imageSize.y;

	butSize = sf::Vector2f(width, height);

	imageSize = Manager::TextureManager::get(hbgSprite)->getSize();
	width = imageSize.x;
	height = imageSize.y;

	sf::Vector2f healthSize = sf::Vector2f(width, height);

	hb = new GUI::HealthBar(*Manager::TextureManager::get(hbgSprite), *Manager::TextureManager::get(hbarSprite), healthSize, viewUI);

	createClassUI();
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::createClassUI()
{
	switch (characterType)
	{
		case PLAYER_MODE::VESSEL: // VESSEL
			switch(classType)
			{
				case 1: //SHAMAN
					b1 = new GUI::Button(*Manager::TextureManager::get(shamanBtn), butSize, viewUI, onclick);
					b2 = new GUI::Button(*Manager::TextureManager::get(shamanBtn), butSize, viewUI, onclick);
					b3 = new GUI::Button(*Manager::TextureManager::get(shamanBtn), butSize, viewUI, onclick);
				break;
				case 2: //WARRIOR
					b1 = new GUI::Button(*Manager::TextureManager::get(warriorBtn), butSize, viewUI, onclick);
					b2 = new GUI::Button(*Manager::TextureManager::get(warriorBtn), butSize, viewUI, onclick);
					b3 = new GUI::Button(*Manager::TextureManager::get(warriorBtn), butSize, viewUI, onclick);
				break;
			}
			break;
		case PLAYER_MODE::DEITY: // DEITY
			crossHairSGO = new SGO(*Manager::TextureManager::get(crosshairImg));
			crossHairSGO->middleAnchorPoint(true);
			crossHairSGO->sprite().setPosition(viewMain.getCenter());
			switch(classType)
			{
				case 1: //VITALITY
					b1 = new GUI::Button(*Manager::TextureManager::get(healskillbtn), skillbtn, viewUI, onClickVitalityOne);
					b2 = new GUI::Button(*Manager::TextureManager::get(buffskillbtn), skillbtn, viewUI, onClickVitalityTwo);
					b3 = new GUI::Button(*Manager::TextureManager::get(healingcircleskillbtn), skillbtn, viewUI, onClickVitalityThree);
				break;
				case 2: //DEMISE
					b1 = new GUI::Button(*Manager::TextureManager::get(hurtskillbtn), skillbtn, viewUI, onClickDemiseOne);
					b2 = new GUI::Button(*Manager::TextureManager::get(debuffskillbtn), skillbtn, viewUI, onClickDemiseTwo);
					b3 = new GUI::Button(*Manager::TextureManager::get(summonskillbtn), skillbtn, viewUI, onClickDemiseThree);
				break;
			}
			break;
		case PLAYER_MODE::GHOST: // GHOST
			b1 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
			b2 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
			b3 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
			break;
		default: //ORIGINAL
			b1 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
			b2 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
			b3 = new GUI::Button(*Manager::TextureManager::get(butSprite), butSize, viewUI, onclick);
	}

	bs[0].btn = b1;
	bs[1].btn = b2;
	bs[2].btn = b3;

}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void GameScene::checkBtns(sf::Time t)
{
		for(int i = 0; i<3; i++)
		{
			if(bs[i].coolDown > 0) //Update cooldown if cooldown was set
			{
				bs[i].coolDown -= t.asMilliseconds();
				if(bs[i].coolDown < 0) //make sure coolDown does not go below 0
				{
					bs[i].coolDown = 0;
				}
			}

			if(bs[i].coolDown > 0) //Check current new cooldown
			{
				bs[i].btn->toggleEnabled(false);
			}
			else
			{
				bs[i].btn->toggleEnabled(true);
			}
		}
}


/*

void CommandEntity::SendSkill(float curX, float curY, int radius, int value, int skilltype)
SKILLTYPE
	0 = -DMG/+HEAL
	1 = -DEBUFF/+BUFF

*/
void onClickVitalityOne() //healskillbtn
{
	bs[0].coolDown = 1000; cout << "COOLDOWN:" << bs[0].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(convertX(vm.getCenter().x), convertY(vm.getCenter().y), 2, 100, SKILLTYPE::HEAL);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onClickVitalityTwo()//buffskillbtn
{
	bs[1].coolDown = 2000; cout << "COOLDOWN:" << bs[1].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(convertX(vm.getCenter().x), convertY(vm.getCenter().y), 2, 1, SKILLTYPE::BUFF);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onClickVitalityThree() //healingcircleskillbtn
{
	bs[2].coolDown = 5000; cout << "COOLDOWN:" << bs[2].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(convertX(vm.getCenter().x), convertY(vm.getCenter().y), 4, 100, SKILLTYPE::HEAL);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onClickDemiseOne() //hurtskillbtn
{
	bs[0].coolDown = 1000; cout << "COOLDOWN:" << bs[0].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(convertX(vm.getCenter().x), convertY(vm.getCenter().y), 2, 100, SKILLTYPE::DMG);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onClickDemiseTwo() //debuffskillbtn
{
	bs[1].coolDown = 2000; cout << "COOLDOWN:" << bs[1].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(convertX(vm.getCenter().x), convertY(vm.getCenter().y), 2, 1, SKILLTYPE::DEBUFF);
}


/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void onClickDemiseThree() //summonskillbtn
{
	bs[2].coolDown = 5000; cout << "COOLDOWN:" << bs[2].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(convertX(vm.getCenter().x), convertY(vm.getCenter().y), 0, 0, SKILLTYPE::SPAWN);
}

float convertX(float x)
{
	float newCoord;
	newCoord = (x - myMap->getGlobalTransform().transformPoint(0,0).x)/32;
	return newCoord;
}

float convertY(float y)
{
	float newCoord;
	newCoord = (y - myMap->getGlobalTransform().transformPoint(0,0).y)/32;
	return newCoord;
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: addSkillNotification
--
-- DATE: April 5, 2015
--
-- DESIGNER: Julian Brandrick
--
-- PROGRAMMER: Julian Brandrick
--
-- INTERFACE: void addSkillNotification(float _x, float _y, int timer, SKILLTYPE _skillType)
--
-- PARAMETERS:
--		_x 			-> The x coordinate of the cast event
--		_y 			-> The y coordinate of the cast event
--		timer 		-> The duration of the cast event
--		_skillType 	-> The skill type of the event
--
-- NOTES:
--  Creates a skill_notify struct and initializes its timer and VEntity. This is then pushed onto the skill 
--	 notification queue.
----------------------------------------------------------------------------------------------------------------------*/
void GameScene::addSkillNotification(float _x, float _y, int timer, SKILLTYPE _skillType)
{
	skill_notify sn;
	SGO *snSGO;
	
	sn.timer = timer;
	
	switch(_skillType)
	{
		case SKILLTYPE::HEAL:
			snSGO = new SGO(*Manager::TextureManager::get(deityHLGImg));
		break;
		case SKILLTYPE::DMG:
			snSGO = new SGO(*Manager::TextureManager::get(deityDMGImg));
		break;
		case SKILLTYPE::BUFF:
			snSGO = new SGO(*Manager::TextureManager::get(deityBUFImg));
		break;
		case SKILLTYPE::DEBUFF:
			snSGO = new SGO(*Manager::TextureManager::get(deityDBFImg));
		break;
	}
	
	sn.entity = new VEntity(*snSGO, cMap, _x, _y, NULL, 1, 1);
	
	snSGO->middleAnchorPoint(true);
	
	snQueue.push_back(sn);
}

/*----------------------------------------------------------------------------------------------------------------------
-- FUNCTION: updateSkillGraphics
--
-- DATE: April 5, 2015
--
-- DESIGNER: Julian Brandrick
--
-- PROGRAMMER: Julian Brandrick
--
-- INTERFACE: void updateSkillGraphics(sf::timer t)
--
-- PARAMETERS:
--		t -> A timer used to measure the duration of the cast event
--
-- NOTES:
--  Interates through the skill notification queue and checks to see if a duration has finished.
--	 If one has then the event's VEntity is deleted and it is popped off of the queue..
----------------------------------------------------------------------------------------------------------------------*/
void GameScene::updateSkillGraphics(sf::Time t)
{
	for(auto it = snQueue.begin(); it != snQueue.end(); it++)
	{
		
		it->timer -= t.asMilliseconds();
		
		if(it->timer <= 0)
		{
			//delete it->entity;
			it->entity->onDestroy();
			snQueue.pop_front();
		}
	}
}

void GameScene::addKeyListener(KeyListener* listener)
{
	keyListeners.insert(listener);
}
