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
#include "../Engine/VEntity.h"
#include "../Engine/EGTheSpinner.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"
#include "../Multimedia/graphics/Animation.h"
#include "../Multimedia/gui/Button.h"
#include "../Multimedia/gui/TextBox.h"
#include "../Multimedia/gui/HealthBar.h"
#include "../Multimedia/manager/SoundManager.h"
#include "../Multimedia/manager/MusicManager.h"
#include "../Network/NetworkEntity.h"
#include "Entities/Vessel.h"
#include "../Logic/PlayerMode.h"

#include "KeyListener.h"
#include "ClickListener.h"

/* The water buffer around the island */
#define WATER_BUFFER 20

/* Amount to add to wave phase per frame */
#define WAVE_PHASE_CHANGE 0.005
#define WAVE_X 5.0
#define WAVE_Y 2.5

/*
*	This is the In-game Scene where all round-events occur.
*/
struct btnStatus
{
	GUI::Button* btn;
	int coolDown = 0;
};

void onClickDemiseThree();
void onClickDemiseTwo();
void onClickDemiseOne();
void onClickVitalityThree();
void onClickVitalityTwo();
void onClickVitalityOne();

static btnStatus bs[3];


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
		void addClickListener(ClickListener* listener);
		void rmClickListener(ClickListener* listener);

		void generateMap(int seed);
		void generateWater();
		void generateUI();
		void positionUI();
		void setPlayerVessel(Vessel *vessel);
        void stopAllSounds();


		friend void onClickVitalityOne();
		friend void onClickVitalityTwo();
		friend void onClickVitalityThree();
		friend void onClickDemiseOne();
		friend void onClickDemiseTwo();
		friend void onClickDemiseThree();

	private:
		/**
		 * set of registered key listeners that should be notified whenever a
		 *   keyboard event occurs.
		 */
		std::set<KeyListener*> keyListeners;
		std::set<ClickListener*> clickListeners;

		// Renderer & views

		Renderer renderer;
		sf::View viewMain;
		sf::View viewUI;
		sf::View viewMinimap;
		sf::RectangleShape minimapBorder;

		// Resources

		static id_resource tilemap;

		static id_resource hbarSprite;
		static id_resource hbgSprite;

		static id_resource butSprite;
		static id_resource demiseBtn;
		static id_resource vitalityBtn;
		static id_resource warriorBtn;
		static id_resource shamanBtn;

		static id_resource crosshairImg;

		//VITALITY
		static id_resource buffskillbtn;
		static id_resource healskillbtn;
		static id_resource healingcircleskillbtn;

		//DEMISE
		static id_resource debuffskillbtn;
		static id_resource hurtskillbtn;
		static id_resource summonskillbtn;

		sf::Shader waveShader;
		float phase;

		// Game Objects

		Marx::Map *cMap;
		Marx::Map *waterMap;

		Vessel *myVessel;

		// UI

		GUI::Button *b1;
		GUI::Button *b2;
		GUI::Button *b3;
		GUI::TextBox *tb;
		GUI::HealthBar *hb;
		GUI::TextBox *levelInd;
		SGO *crossHairSGO;

		// Misc

		GameMap *gMap;

		PLAYER_MODE characterType;
		int classType;

		sf::Sound current;

		// tech demos:
		sf::Vector2f butSize;
		const sf::Vector2f skillbtn = sf::Vector2f(24,24);

		void checkBtns(sf::Time);
		void createClassUI();
};

#endif
