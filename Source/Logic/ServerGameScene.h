#ifndef SERVER_GAME_SCENE_H_
#define SERVER_GAME_SCENE_H_

#include <vector>
#include <cstdio>
#include <map>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"

#include "Environment/GameMap.h"
#include "EnemyTypes.h"
#include "PlayerMode.h"

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
        void createEnemy(ENEMY_TYPES type, Behaviour *behaviour, float x, float y);

    private:
        SGO gkSGO;
        Marx::Map *cMap;
        GameMap *gMap;
        sf::View viewMain;
        ServerCommand *command;
        int worldSeed;
        std::vector<Creature*> enemies;
};

#endif
