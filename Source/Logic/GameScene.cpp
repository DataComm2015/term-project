#include "GameScene.h"

using namespace Marx;


GameScene::GameScene() : renderer(AppWindow::getInstance(), 4000)
{
	cMap = new Map(40, 40);
	gMap = new GameMap(cMap);
}


GameScene::~GameScene()
{
	delete gMap;
	delete cMap;
}


void GameScene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void GameScene::processEvents(sf::Event& e)
{
	if( e.type == sf::Event::KeyPressed )
	{
		// Generate the game map
		gMap->generateMap();
	}
}

void GameScene::draw()
{
	AppWindow& window = AppWindow::getInstance();
	
	window.clear();
	window.display();
}
