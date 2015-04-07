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

#define BTN_SIZE 200

#define SERVER_TXT 0
#define PORT_TXT 1
#define NICKNAME_TXT 2
#define TEXT_BOXES 3

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
        void updateMainView(sf::View& v);
        friend void nextTextBox( void * );

    private:
        sf::View viewMain;
        Renderer renderer;

        SGO *background;
        id_resource backgroundImg;

        GUI::Label * serverLbl;
        GUI::Label * portLbl;
        GUI::Label * nicknameLbl;

        GUI::TextBox * textBoxes[ TEXT_BOXES ];
        int curTextBox;

        GUI::Button * connectBtn;
        id_resource connectImg;
};
void nextTextBox( void * data );

#endif