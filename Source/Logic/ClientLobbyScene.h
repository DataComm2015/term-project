#ifndef CLIENT_LOBBY_SCENE_H_
#define CLIENT_LOBBY_SCENE_H_

#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Engine/Scene.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"
#include "../Multimedia/gui/Button.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/object/SGO.h"

#include "../Network/Client.h"
#include "Entities/ClientMux.h"
#include "PlayerLobbyChoices.h"

#define BTN_WIDTH 150
#define BTN_HEIGHT 75
#define COUNTDOWN 4

#define CLASS_BTN_WIDTH 48
#define CLASS_BTN_HEIGHT 49

#define CLASS_BTN_WIDTH_B 52
#define CLASS_BTN_HEIGHT_B 53

#define BACK_BTN_WIDTH 48
#define BACK_BTN_HEIGHT 17

/*
*   This is the Lobby scene.
*/
class ClientLobbyScene : public Scene
{
    public:
        ClientLobbyScene(bool isfake=false);
        virtual void update(sf::Time);
        virtual void processEvents(sf::Event&);
        virtual void draw();
        virtual void onLoad();
        ~ClientLobbyScene();

        static void onLeaveClick();
        static void onVesselOneClick();
        static void onVesselTwoClick();
        static void ondeityVitalityClick();
        static void ondeityDemiseClick();
        void updateMainView(sf::View& v);
        static int vesselChoice;
        static int deityChoice;
        static int click;

        void startTimer(int remainingTime);
        void stopTimer(int remainingTime);
        void updatePlayerCount(int numPlayers);

        PlayerLobbyChoices *getSelections();
    private:

        sf::View viewMain;
        Renderer renderer;

        double height;
        double cur_movement;
        double speed;
        double total_movement;
        double height_mov;
        bool fake_lobby;

        SGO *background;
        id_resource backgroundImg;

        id_resource circle;
        GUI::TextBox * countdownBox;
        GUI::TextBox * playerBox;

        SGO *vesselOneCircleSGO;
        SGO *vesselTwoCircleSGO;
        SGO *deityVitalityCircleSGO;
        SGO *deityDemiseCircleSGO;

        SGO *vesselOneSGO;
        SGO *vesselTwoSGO;

        SGO *deityVitalitySGO;
        SGO *deityDemiseSGO;

        SGO *playerTwoSGO;
        SGO *playerThreeSGO;
        SGO *playerFourSGO;

        SGO *playerTwoShadowSGO;
        SGO *playerThreeShadowSGO;
        SGO *playerFourShadowSGO;

        SGO *vesselShadowSGO;

        GUI::Button * vesselOneBtn;
        GUI::Button * vesselTwoBtn;

        GUI::Button * deityVitalityBtn;
        GUI::Button * deityDemiseBtn;

        GUI::Button * leaveBtn;

        id_resource vesselOneArt;
        id_resource vesselTwoArt;

        id_resource otherPlayerArt;

        id_resource vesselOneImg;
        id_resource vesselTwoImg;

        id_resource deityVitalityImg;
        id_resource deityDemiseImg;

        id_resource deityVitalityArt;
        id_resource deityDemiseArt;

        id_resource vesselShadowImg;

        id_resource leaveImg;

        const int SCN_WIDTH = 1366;
        const int SCN_HEIGHT = 768;

        const int CIRCLE_WH = 200;
        const int VESSEL_ART_H = 56;
        const int VESSEL_ART_W = 64;

        const int EASTER_ART_HW = 400;

        const int MAX_SCROLL = 188;

        static sf::Clock clck;

        static int currScrollHeight;

        static bool timego;
        static float currentTime;
        int playerCount;

        GameScene * gameScene;
        ClientMux * clientMux;
        PlayerLobbyChoices playerSelections;

        sf::Sound title;
};

#endif
