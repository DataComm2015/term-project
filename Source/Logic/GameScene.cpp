#include "EG_Scene.h"

using namespace Marx;


GameScene::GameScene()
{
	cMap = new Map(40, 40);
	gMap = new GameMap(cMap);
}


GameScene::~GameScene()
{
	delete gMap;
	delete cMap;
}


void EG_Scene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void EG_Scene::processEvents(sf::Event& e)
{
	if( e.type == sf::Event::KeyPressed )
	{
		// Generate the game map
		GameMap->generateMap();
	}
}

void EG_Scene::draw()
{
	AppWindow * window = AppWindow::getInstance();
	
	window->clear();

	// Draw the game map

	window->display();
}
