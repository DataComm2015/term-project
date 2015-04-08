#ifndef MAIN_MENU_SCENE_H_
#define MAIN_MENU_SCENE_H_

#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/gui/Button.h"
#include "../Multimedia/gui/TextBox.h"
#include "../Multimedia/gui/Label.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/graphics/object/TGO.h"
#include "../Network/Client.h"
#include "Entities/ClientMux.h"
#include "CreditScene.h"

#define BTN_SIZE 200
#define BANNER_W 400
#define BANNER_H 400

#define SERVER_TXT 0
#define PORT_TXT 1
#define NICKNAME_TXT 2
#define TEXT_BOXES 3

#define CLASS_BTN_WIDTH 48
#define CLASS_BTN_HEIGHT 49

class GameScene;
class ClientLobbyScene;
class ClientScoreboardScene;

/*
*   This is the Lobby scene.
*/
class MainMenuScene : public Scene
{
    public:
        static MainMenuScene * getInstance();
        MainMenuScene();
        virtual void update(sf::Time);
        virtual void processEvents(sf::Event&);
        virtual void draw();
        virtual void onLoad();
        ~MainMenuScene();

        static void onClick();
        static void onClickCredit();
        void updateMainView(sf::View& v);
        friend void nextTextBox( void * );

        static GameScene *getGameScene();
        static void clearGameScene();
    private:
        static GameScene *gameScene;
        Networking::Client *client;
        ClientLobbyScene *lobbyScene;
        ClientScoreboardScene* scoreScene;
        ClientMux* clientmux;
        sf::View viewMain;
        Renderer renderer;

        char* name_sent;

        SGO *background;
        SGO *serverTextBackground;
        SGO *portTextBackground;
        SGO *nicknameTextBackground;
        SGO *serverTextBackgroundBox;
        SGO *portTextBackgroundBox;
        SGO *nicknameTextBackgroundBox;

        SGO *banner;

        id_resource bannerImg;
        id_resource backgroundImg;
        id_resource textBackgroundImg;
        id_resource textBackgroundBoxImg;

	id_resource menuMsc;

	sf::Music *music;

        GUI::Label * serverLbl;
        GUI::Label * portLbl;
        GUI::Label * nicknameLbl;

        GUI::TextBox * textBoxes[ TEXT_BOXES ];
        GUI::TextBox * connectFailedText;
        int curTextBox;

        GUI::Button * connectBtn;
        id_resource connectImg;

        GUI::Button * creditBtn;
        id_resource creditImg;

        const float FONT_SCALE = 0.7;
        const float FONT_OFFSET = 1 + ((1 - FONT_SCALE) * 1/2);

        const int SCN_WIDTH = 1366;
        const int SCN_HEIGHT = 768;
        const int TEXT_W = 148;
        const int TEXT_H = 24;
        const int TEXT_BOX_W = 152;
        const int TEXT_BOX_H = 26;

        const int WIDE_BUTTONS_W = 64;
        const int WIDE_BUTTONS_H = 31;

        const int textw = SCN_WIDTH/2 + 114  - TEXT_W/2;
        const int text1_h = SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*1;
        const int text2_h = SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*2;
        const int text3_h = SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*3;

        const int text_b_w = SCN_WIDTH/2 + 114 - TEXT_BOX_W/2;
        const int text1_b_h = SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*1;
        const int text2_b_h = SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*2;
        const int text3_b_h = SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*3;

        static bool connectFailed;

        const char* connectFailErr = "FAILED TO CONNECT";

};
void nextTextBox( void * data );

#endif
