#include "EG_Scene.h"

using namespace Marx;

void EG_Scene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void EG_Scene::processEvents(sf::Event& e)
{
	printf("%d\n", e.type);
}