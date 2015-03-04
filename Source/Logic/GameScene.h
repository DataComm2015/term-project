#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "Environment/GameMap.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"

/*
* Testing Game Scene
*/
class GameScene : public Scene
{
	public:
		GameScene();
		virtual void update(sf::Time);
		virtual void processEvents(sf::Event&);
		virtual void draw();
		~GameScene();
	private:
		Marx::Map *cMap;
		GameMap *gMap;
    	Renderer renderer;
};

#endif