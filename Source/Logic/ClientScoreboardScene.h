#ifndef CLIENT_SCOREBOARD_SCENE_H_
#define CLIENT_SCOREBOARD_SCENE_H_

#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"

#include "../Network/Client.h"
#include "Entities/ClientMux.h"
#include "../GameSettings.h"

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define SCORE_ROWS 13 // max players + 1
#define SCORE_COLS  3 // name, (deity or vessel), score

#define SCORE_X  220 // starting position for the scoreboard
#define SCORE_Y  80  // starting position for the scoreboard
#define OFFSET_X 150 // offset for each col in the scoreboard
#define OFFSET_Y 20 // offset for each row in the scoreboard

#define C_BOX_X 65
#define C_BOX_Y 30

#define SCALE 0.8

#define SCORE_COUNTDOWN 10

/*
*   This is the Lobby scene.
*/
class ClientScoreboardScene : public Scene
{
    public:

        Player* data_received;

        ClientScoreboardScene();
        virtual void update(sf::Time);
        virtual void processEvents(sf::Event&);
        virtual void draw();
        virtual void onLoad();
        ~ClientScoreboardScene();

        void updateMainView(sf::View& v);
        
        static ClientScoreboardScene * getInstance();

        void setScoreboard(Player* players);

    private:

        sf::View viewMain;
        Renderer renderer;

        SGO *background;
        id_resource backgroundImg;

        GUI::TextBox scoreboard[SCORE_ROWS][SCORE_COLS];

        static float currentTime;

        GameScene * gameScene;
        ClientMux * clientMux;
        
        char * SCORE_ELEMENTS[SCORE_COLS];
        
        GUI::TextBox * countdownBox;
};

#endif
