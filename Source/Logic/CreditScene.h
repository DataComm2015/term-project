#ifndef CREDIT_SCENE_H_
#define CREDIT_SCENE_H_

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

class MainMenuScene;


#define BTN_SIZE 200

/*
*   This is the Lobby scene.
*/
class CreditScene : public Scene
{
    public:
        static CreditScene * getInstance();
        CreditScene(MainMenuScene*);
        virtual void update(sf::Time);        
        virtual void processEvents(sf::Event&);
        virtual void draw();
        virtual void onLoad();
        ~CreditScene();

        static void onClick();
        void updateMainView(sf::View& v);

    private:
        sf::View viewMain;
        Renderer renderer;

        MainMenuScene* mainmenu;

        SGO *background;
        id_resource backgroundImg;

        SGO *creditText;
        id_resource creditImg;

        GUI::Button * backBtn;
        id_resource backImg;

	sf::Music *music;
	id_resource credits_msc;
	sf::Music *lord;
	id_resource lord_msc;

};
void nextTextBox( void * data );

#endif
