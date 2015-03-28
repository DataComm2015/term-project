#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include <set>
#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Engine/Scene.h"
#include "Environment/GameMap.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Engine/TileManager.h"
#include "../Engine/ProjectileManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"
#include "../Logic/Champion/Vessel.h"
#include "../Multimedia/graphics/Animation.h"
#include "../Multimedia/gui/Button.h"
#include "../Multimedia/gui/TextBox.h"
#include "../Multimedia/manager/SoundManager.h"
#include "../Multimedia/manager/MusicManager.h"
#include "../Engine/VEntity.h"
#include "../Engine/EGTheSpinner.h"

#include "KeyListener.h"

/* The water buffer around the island */
#define WATER_BUFFER 20

/* Amount to add to wave phase per frame */
#define WAVE_PHASE_CHANGE 0.005
#define WAVE_X 5.0
#define WAVE_Y 2.5

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
		Marx::Map* getcMap() { return cMap; }
		void onLoad();
		void unLoad();
		~GameScene();

		void addKeyListener(KeyListener* listener);
		void rmKeyListener(KeyListener* listener);

		void generateWater();
		void generateUI();
		void positionButtons();
		
	private:
		/**
		 * set of registered key listeners that should be notified whenever a
		 *   keyboard event occurs.
		 */
		std::set<KeyListener*> keyListeners;

		GameMap *gMap;

		Renderer renderer;

		sf::View viewMain;
		sf::View viewUI;

		sf::Sound current;

		id_resource tilemap;
		id_resource championSprite;
		id_resource maskSprite;
		id_resource wepSprite;
		id_resource butSprite;
		id_resource scat_music;
		id_resource chick_sound;
		id_resource placeholderSprite;

		sf::Shader waveShader;
		float phase;

		// Game Objects

		Marx::Map *cMap;
		Marx::Map *waterMap;
		Marx::Projectile * p;

		SGO championSGO;
		SGO maskSGO;
		SGO wepSGO;
		SGO placeHolderSGO;
		Vessel *v;
		TheSpinner *s;
		TheSpinner *s2;

		// UI
		GUI::Button *b1;
		GUI::Button *b2;
		GUI::Button *b3;
		GUI::Button *b4;
		GUI::Button *b5;
		GUI::Button *b6;
		GUI::TextBox *tb;
};

#endif
