#include "GameScene.h"
#include "Entities/CommandEntity.h"
#include "PlayerLobbyChoices.h"
#include "Skills.h"
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

GUI::TextBox *pubLevelInd;
void onclickLevelup()
{
	static int level = 1;
	std::string slevel;

	// level should be double digits
	if(level < 10)
		slevel = "0" + std::to_string(level++);
	else
		slevel = std::to_string(level++);
	pubLevelInd->setText(slevel);
}

void updateMainView(sf::View& v)
{
	v = AppWindow::getInstance().getCurrentView();
	v.zoom(0.33);
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
			Cell *tempCell = new Cell(j, i);
			tempCell->setTileId(1);

			cMap->setCell(j, i, tempCell);
		}
	}
	gMap = new GameMap(cMap);
	waterMap = new Map(cMap->getWidth() + WATER_BUFFER, cMap->getHeight() + WATER_BUFFER);

	myVessel = NULL;

	std::cout << "making tileset" << std::endl;
	// Load the tileset
	tilemap = Manager::TileManager::load("Assets/Tiles/map.tset");

	butSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/button.png"));
	placeholderSprite = Manager::TextureManager::store(
		Manager::TextureManager::load("Assets/Art/Misc/placeholder_32.png")
		);

	//scat_music = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Sound/music.ogg"));
	//chick_sound = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/sound.ogg"));

	cMap->setTexture(tilemap);

	placeHolderSGO.sprite().setTexture(*Manager::TextureManager::get(placeholderSprite));
	placeHolderSGO.middleAnchorPoint(true);

	s = new TheSpinner(placeHolderSGO, cMap, 25, 25, 5, 1);
	s2 = new TheSpinner(placeHolderSGO, cMap, 25, 35, 5, -1);

	sf::Font *arial = new sf::Font();
	arial->loadFromFile("Assets/Fonts/arial.ttf");

	tb = new GUI::TextBox(NULL, NULL);
	tb->text().setScale(0.5, 0.5);
	tb->text().move(0, -5);
	tb->toggleSelected(true);
	tb->text().setFont(*arial);

	// Generate stuff

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
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	characterType = cm->getCommandEntity()->getPlayerMode();
	switch (characterType)
	{
		case PLAYER_MODE::VESSEL:
			classType = cm->getCommandEntity()->getLobbyOption()->vesselChoice;
		case PLAYER_MODE::DEITY:
			classType = cm->getCommandEntity()->getLobbyOption()->deityChoice;
	}

	printf("characterType: %d, classType: %d\n",characterType,classType);

	// update views
	updateMainView(viewMain);
	viewUI = AppWindow::getInstance().getCurrentView();

	// minimap view
	viewMinimap = viewMain;
	viewMinimap.setViewport(sf::FloatRect(0.76f,0.01f,0.23f,0.23f));
	viewMinimap.zoom(2.f);


	// position buttons
	generateUI();
	positionUI();

	// Enable buttons
	b1->toggleEnabled(true);
	b2->toggleEnabled(true);
	b3->toggleEnabled(true);

//	Manager::MusicManager::get(scat_music)->setVolume(60);
//	Manager::MusicManager::get(scat_music)->play();
}


void GameScene::positionUI()
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

	// position and scale level indicator
	levelInd->text().setPosition(15, 10);
	levelInd->text().setScale(1.5, 1.5);
}

void GameScene::setPlayerVessel(Vessel *vessel)
{
	myVessel = vessel;
}

void GameScene::unLoad()
{
	b1->toggleEnabled(false);
	b2->toggleEnabled(false);
	b3->toggleEnabled(false);

	//Manager::MusicManager::get(scat_music)->stop();
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


/**
--
--	PROGRAMMER: ???
--				Sanders Lee (Fixed hearing center for sounds)
--
**/
void GameScene::update(sf::Time t)
{
	checkBtns(t);
	// static int listEntity = 100;
	auto entities = cMap->getEntities();
	for ( auto it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->onUpdate(t.asSeconds());
	}

	if (myVessel != NULL) // SHOULD MOVE THIS INTO VESSEL's UPDATE FUNCTION
	{
		//to test:
		//myVessel->getSprite().sprite().rotate(1);

		viewMain.setCenter(myVessel->getGlobalTransform().transformPoint(16,16));

		viewMinimap.setCenter(myVessel->getGlobalTransform().transformPoint(16,16));
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

	if(myVessel != NULL)
	{
		sf::Listener::setPosition(myVessel->left, myVessel->top, 0);
	}

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


	//cMap->setPosition(cMap->getWidth() * 0.5f * -32, cMap->getHeight() * 0.5f * -32);
	//waterMap->setPosition(waterMap->getWidth() * 0.5f * -32, waterMap->getHeight() * 0.5f * -32);

	// Increment the wave phase
	phase += WAVE_PHASE_CHANGE;
	waveShader.setParameter("wave_phase", phase);
}

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
					break;
				}
				case sf::Keyboard::Right:
				{
					viewMain.setCenter(viewMain.getCenter().x + camSpeed, viewMain.getCenter().y);
					break;
				}
				case sf::Keyboard::Up:
				{
					viewMain.setCenter(viewMain.getCenter().x, viewMain.getCenter().y - camSpeed);
					break;
				}
				case sf::Keyboard::Down:
				{
					viewMain.setCenter(viewMain.getCenter().x, viewMain.getCenter().y + camSpeed);
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
	else if (e.type == sf::Event::Resized)
	{
		// update views
		updateMainView(viewMain);
		viewUI = AppWindow::getInstance().getCurrentView();
		viewMinimap = AppWindow::getInstance().getCurrentView();
		positionUI();
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if(characterType == PLAYER_MODE::VESSEL)
		{
			sf::Vector2i mouse = sf::Mouse::getPosition();
			sf::Vector2f viewVector = viewMain.getCenter();
			std::cout << "Mouse clicked: " << mouse.x << " " << mouse.y << std::endl;
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
	}

	if(characterType == PLAYER_MODE::VESSEL)
	{
		renderer.draw(hb);
		renderer.draw(levelInd);
	}
	renderer.end();

	//the border for the minimap
	minimapBorder.setSize(
		sf::Vector2f(viewMinimap.getViewport().width*window.getSize().x,
			     viewMinimap.getViewport().height*window.getSize().y));

	minimapBorder.setPosition(
		sf::Vector2f(viewMinimap.getViewport().left*window.getSize().x,
		  	     viewMinimap.getViewport().top*window.getSize().y));

	minimapBorder.setFillColor(sf::Color::Black);
	minimapBorder.setOutlineThickness(5); //thickness set to 5 pixels

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

void GameScene::addKeyListener(KeyListener* listener)
{
	keyListeners.insert(listener);
}

void GameScene::rmKeyListener(KeyListener* listener)
{
	keyListeners.erase(listener);
}

void GameScene::addClickListener(ClickListener* listener)
{
	clickListeners.insert(listener);
}

void GameScene::rmClickListener(ClickListener* listener)
{
	clickListeners.erase(listener);
}

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


void GameScene::generateUI()
{
	// Create buttons
	butSprite = Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Menu/shaman-btn.png"));

	demiseBtn = Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Menu/demise-btn.png"));
	vitalityBtn = Manager::TextureManager::store(Manager::TextureManager::load(	"Assets/Art/GUI/Menu/vitality-btn.png"));
	warriorBtn = Manager::TextureManager::store(Manager::TextureManager::load(	"Assets/Art/GUI/Menu/warrior-btn.png"));
	shamanBtn = Manager::TextureManager::store(Manager::TextureManager::load(	"Assets/Art/GUI/Menu/shaman-btn.png"));



	buffskillbtn						= Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Deity/buff-skill-btn.png"));
	healskillbtn						= Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Deity/heal-skill-btn.png"));
	healingcircleskillbtn	= Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Deity/healingcircle-skill-btn.png"));
	debuffskillbtn					= Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Deity/debuff-skill-btn.png"));
	hurtskillbtn						= Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Deity/hurt-skill-btn.png"));
	summonskillbtn					= Manager::TextureManager::store(Manager::TextureManager::load(		"Assets/Art/GUI/Deity/summon-skill-btn.png"));


	sf::Vector2u imageSize = Manager::TextureManager::get(butSprite)->getSize();
	unsigned int width = imageSize.x / 4;
	unsigned int height = imageSize.y;

	butSize = sf::Vector2f(width, height);

	setUI();

	// Create health bar (If statement here if vessel or deity)
	hbarSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/HUDhealthbar.png"));
	hbgSprite = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/HUDbase.png"));

	imageSize = Manager::TextureManager::get(hbgSprite)->getSize();
	width = imageSize.x;
	height = imageSize.y;

	sf::Vector2f healthSize = sf::Vector2f(width, height);

	hb = new GUI::HealthBar(*Manager::TextureManager::get(hbgSprite), *Manager::TextureManager::get(hbarSprite), healthSize, viewUI);

	pubHB = hb;

	// Create level indicator

	sf::Font *arial = new sf::Font();
	arial->loadFromFile("Assets/Fonts/arial.ttf");

	levelInd = new GUI::TextBox(nullptr, nullptr);
	levelInd->toggleSelected(true);
	levelInd->text().setFont(*arial);
	levelInd->setText("01");
	pubLevelInd = levelInd;
}

void GameScene::setUI()
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
		}break;
		case PLAYER_MODE::DEITY: // DEMISE
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
			}break;
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
	sf::View vm;
	vm = AppWindow::getInstance().getCurrentView();
	bs[0].coolDown = 1000; cout << "COOLDOWN:" << bs[0].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(vm.getCenter().x, vm.getCenter().y, 10, 100, SKILLTYPE::HEAL);
}
void onClickVitalityTwo()//buffskillbtn
{
	sf::View vm;
	vm = AppWindow::getInstance().getCurrentView();
	bs[1].coolDown = 2000; cout << "COOLDOWN:" << bs[1].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(vm.getCenter().x, vm.getCenter().y, 10, 100, SKILLTYPE::BUFF);
}
void onClickVitalityThree() //healingcircleskillbtn
{
	sf::View vm;
	vm = AppWindow::getInstance().getCurrentView();
	bs[2].coolDown = 5000; cout << "COOLDOWN:" << bs[2].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(vm.getCenter().x, vm.getCenter().y, 50, 100, SKILLTYPE::HEAL);
}
void onClickDemiseOne() //hurtskillbtn
{
	sf::View vm;
	vm = AppWindow::getInstance().getCurrentView();
	bs[0].coolDown = 1000; cout << "COOLDOWN:" << bs[0].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(vm.getCenter().x, vm.getCenter().y, 10, 100, SKILLTYPE::DMG);
}
void onClickDemiseTwo() //debuffskillbtn
{
	sf::View vm;
	vm = AppWindow::getInstance().getCurrentView();
	bs[1].coolDown = 2000; cout << "COOLDOWN:" << bs[1].coolDown << endl;
	ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
	cm->getCommandEntity()->SendSkill(vm.getCenter().x, vm.getCenter().y, 10, 100, SKILLTYPE::DEBUFF);
}
void onClickDemiseThree() //summonskillbtn
{
	bs[2].coolDown = 5000; cout << "COOLDOWN:" << bs[2].coolDown << endl;
}
