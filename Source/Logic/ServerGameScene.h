#ifndef SERVER_GAME_SCENE_H_
#define SERVER_GAME_SCENE_H_

#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "../Logic/Environment/GameMap.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"



/*
*   This is the In-game Scene where all round-events occur.
*/
class ServerGameScene : public Scene
{
    public:
        ServerGameScene();
        virtual void update(sf::Time);
        virtual void processEvents(sf::Event&);
        virtual void draw();
        Marx::Map* getcMap() { return cMap; }
        ~ServerGameScene();

    private:
        Marx::Map *cMap;
        GameMap *gMap;

        sf::View viewMain;
};

#endif
