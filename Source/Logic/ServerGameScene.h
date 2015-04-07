
#ifndef SERVER_GAME_SCENE_H_
#define SERVER_GAME_SCENE_H_

#include <vector>
#include <cstdio>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../Engine/Scene.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"

#include "Environment/GameMap.h"
#include "PlayerMode.h"

#define SYNC_INTERVAL 1

class ServerEnemyController;
class ServerCommand;
class Creature;
class Behaviour;

/*
*   This is the In-game Scene where all round-events occur.
*/
class ServerGameScene : public Scene
{
    public:
        ServerGameScene(ServerCommand *command);
        virtual void update(sf::Time);
        virtual void processEvents(sf::Event&);
        virtual void draw();
        Marx::Map* getcMap() { return cMap; }
        ~ServerGameScene();

        void enterScene();
        void leaveScene();
        int getWorldSeed();
        void createPlayers();
	//void createProjectile(Marx::Action&, float, float);
        void createEnemy(ENTITY_TYPES type, Behaviour *behaviour, float x, float y);
        void createStructure(ENTITY_TYPES type, float x, float y);

        std::vector<Vessel*> *getPlayerList();

    private:
        SGO gkSGO;
        Marx::Map *cMap;
        GameMap *gMap;
        sf::View viewMain;
        ServerCommand *command;
        int worldSeed;
        float timer;
        float syncTimer;
        float lobtimer;
        std::vector<Creature*> enemies;
        std::vector<ServerEnemyController*> enemyControllers;
        std::vector<Vessel*> playerList;

        bool gameShouldEnd();
};

#endif
