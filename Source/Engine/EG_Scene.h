#ifndef EG_SCENE_H_
#define EG_SCENE_H_

/**
* The base Scene class can be extended to have other funcitonality, or it can be used as a void
*
*
*
**/
#include <vector>
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../AppWindow.h"
#include <cstdio>
namespace Marx
{
	class EG_Scene : public Scene
	{
	public:
		virtual void update(sf::Time);
		virtual void processEvents(sf::Event&);
		virtual void draw();
		~EG_Scene();
	private:
		sf::CircleShape shape;
	};
}

#endif