#ifndef SCENE_H_
#define SCENE_H_

/**
* The base Scene class can be extended to have other funcitonality, or it can be used as a void
*
*
*
**/
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdio>

namespace Marx
{
	class Scene
	{
	public:
		virtual void onLoad();
		virtual void unLoad();
		virtual void processEvents(sf::Event&);
		virtual void update(sf::Time);
		virtual void draw();
	};
}

#endif