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
#include "../Logic/Champion/Vessel.h"
#include "../Multimedia/graphics/Animation.h"
#include "../Multimedia/gui/Button.h"

/* The water buffer around the island */
#define WATER_BUFFER 10

/* Amount to add to wave phase per frame */
#define WAVE_PHASE_CHANGE 0.007
#define WAVE_X 2.0
#define WAVE_Y 1.0

/*
*	This is the In-game Scene where all round-events occur.
*/
class GameScene : public Scene
{
	public:
		GameScene();
		virtual void update(sf::Time);
		virtual void processEvents(sf::Event&);
		virtual void draw();
		~GameScene();

		void generateWater();
	private:
		Marx::Map *cMap;
		Marx::Map *waterMap;
		GameMap *gMap;

    	Renderer renderer;
    	sf::View viewMain;

    	id_resource tilemap;
    	id_resource championSprite;
    	id_resource maskSprite;
    	id_resource wepSprite;
    	id_resource butSprite;

    	SGO championSGO;
    	SGO maskSGO;
    	SGO wepSGO;
		Vessel *v;
		
		GUI::Button *b1;
    	
    	sf::Shader waveShader;
    	float phase;
};

#endif
