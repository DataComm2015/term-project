#include "EG_Scene.h"

using namespace Marx;

void EG_Scene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void EG_Scene::processEvents(sf::Event& e)
{
	shape = sf::CircleShape(100.f);
	
	if( e.type == sf::Event::KeyPressed )
	{
		shape.setFillColor(sf::Color::Green);
	}
	else if( e.type == sf::Event::MouseButtonPressed )
	{
		shape.setFillColor(sf::Color::Red);
	}
	else
	{
		shape.setFillColor(sf::Color::Yellow);
	}
}

void EG_Scene::draw()
{
	AppWindow * window = AppWindow::getInstance();
	
	window->clear();
    window->draw(shape);
	window->display();
}
