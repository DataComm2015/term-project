/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ClientLobbyScene.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--
-- DATE: March 30, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Calvin Rempel, Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam, Chris Klassen, Michael Chimick, Calvin Rempel, Melvin Loho
--
-- NOTES:
--        This file contains the implementation of the lobby scene for the client.
----------------------------------------------------------------------------------------------------------------------*/


#include "ClientLobbyScene.h"
#include "MainMenuScene.h"
#include <iostream>
#include <SFML/System/Time.hpp>
#include "Entities/ClientMux.h"
#include "Entities/CommandEntity.h"
#include "../Multimedia/manager/SoundManager.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;

using namespace Manager;

int ClientLobbyScene::vesselChoice;
int ClientLobbyScene::deityChoice;
sf::Clock ClientLobbyScene::clck;
bool ClientLobbyScene::timego;
float ClientLobbyScene::currentTime;
int ClientLobbyScene::click;
int ClientLobbyScene::currScrollHeight;


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ClientLobbyScene::ClientLobbyScene() : renderer(AppWindow::getInstance(), 48400)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel, Alex Lam, Chris Klassen and Michael Chimick
--
-- PROGRAMMER: Calvin Rempel, Alex Lam, Chris Klassen and Michael Chimick
--             Sanders Lee (Added title call), Jeff Bayntun
--
-- INTERFACE: ClientLobbyScene::ClientLobbyScene() : renderer(AppWindow::getInstance(), 48400)
--
-- RETURNS: void
--
-- NOTES:
-- Initalizes GUI
-- Loads in artwork
-- Creates background, buttons and textboxes
-- Sets up lobby network logic
----------------------------------------------------------------------------------------------------------------------*/
ClientLobbyScene::ClientLobbyScene(bool isfake) : renderer(AppWindow::getInstance(), 48400)
{
    /* Get texture assets */
    // as art assets are created for these, add them

    playerCount = 0;
    vesselChoice = 1;
    deityChoice = 1;
    timego = false;
    click = 0;
    fake_lobby = isfake;

    circle = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/selected.png"));

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/lobby.png"));

    vesselOneArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-img.png"));
    vesselTwoArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-img.png"));

    deityVitalityArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/vitality-img.png"));
    deityDemiseArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/demise-img.png"));

    otherPlayerArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Player/Idle/Body/vessel-idle.png"));

    vesselOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-btn.png"));
    vesselTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));

    deityVitalityImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/vitality-btn.png"));
    deityDemiseImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/demise-btn.png"));

    vesselShadowImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/Shadows/vessel_shadow.png"));

    leaveImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/back-btn.png"));


    /* Initialize buttons */
    vesselOneBtn = new GUI::Button(*Manager::TextureManager::get(vesselOneImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onVesselOneClick);

    vesselTwoBtn = new GUI::Button(*Manager::TextureManager::get(vesselTwoImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onVesselTwoClick);

    deityVitalityBtn = new GUI::Button(*Manager::TextureManager::get(deityVitalityImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, ondeityVitalityClick);
    deityDemiseBtn = new GUI::Button(*Manager::TextureManager::get(deityDemiseImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, ondeityDemiseClick);

    leaveBtn     = new GUI::Button(*Manager::TextureManager::get(leaveImg), sf::Vector2f(BACK_BTN_WIDTH, BACK_BTN_HEIGHT), viewMain, onLeaveClick);

    /*Init artwork*/
    vesselOneSGO = new SGO(*Manager::TextureManager::get(vesselOneArt));
    vesselTwoSGO = new SGO(*Manager::TextureManager::get(vesselTwoArt));

    playerTwoSGO = new SGO(*Manager::TextureManager::get(otherPlayerArt));
    playerThreeSGO = new SGO(*Manager::TextureManager::get(otherPlayerArt));
    playerFourSGO = new SGO(*Manager::TextureManager::get(otherPlayerArt));

    playerTwoShadowSGO = new SGO(*Manager::TextureManager::get(vesselShadowImg));
    playerThreeShadowSGO = new SGO(*Manager::TextureManager::get(vesselShadowImg));
    playerFourShadowSGO = new SGO(*Manager::TextureManager::get(vesselShadowImg));

    deityVitalitySGO = new SGO(*Manager::TextureManager::get(deityVitalityArt));
    deityDemiseSGO = new SGO(*Manager::TextureManager::get(deityDemiseArt));

    vesselOneCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    vesselTwoCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    deityVitalityCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    deityDemiseCircleSGO = new SGO(*Manager::TextureManager::get(circle));

    vesselShadowSGO = new SGO(*Manager::TextureManager::get(vesselShadowImg));

    background = new SGO(*Manager::TextureManager::get(backgroundImg));

    sf::Font *font = new sf::Font();
    font->loadFromFile("Assets/Fonts/hud.ttf");


    countdownBox = new GUI::TextBox(NULL,NULL);
    countdownBox->text().setScale(0.5, 0.5);
    countdownBox->toggleSelected(false);
    countdownBox->text().setFont(*font);

    playerBox = new GUI::TextBox(NULL,NULL);
    playerBox->text().setScale(0.7, 0.7);
    playerBox->toggleSelected(false);
    playerBox->text().setFont(*font);

    sf::Vector2f soundPos;
    id_resource titleSound = SoundManager::store(SoundManager::load("Assets/Sound/Announcer/title.ogg"));
    title = SoundManager::play(titleSound, soundPos);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ClientLobbyScene::~ClientLobbyScene()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: ClientLobbyScene::~ClientLobbyScene()
--
-- RETURNS: void
--
-- NOTES:
-- Deconstructs ClientLobbyScene and cleans up
----------------------------------------------------------------------------------------------------------------------*/
ClientLobbyScene::~ClientLobbyScene()
{
    delete vesselOneBtn;
    delete vesselTwoBtn;

    delete deityVitalityBtn;
    delete deityDemiseBtn;

    delete leaveBtn;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::onLoad()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Chris Klassen and Michael Chimick
--
-- PROGRAMMER: Alex Lam, Chris Klassen and Michael Chimick
--             Sanders Lee (Added title call)
--
-- INTERFACE: void ClientLobbyScene::onLoad()
--
-- RETURNS: void
--
-- NOTES:
-- Sets position of buttons, textboxes and sprites
-- updates main view
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::onLoad()
{
    // Delete GameScene everytime player enters the lobby
    MainMenuScene::clearGameScene();
    MainMenuScene::getGameScene();
    ((ClientMux*)NetworkEntityMultiplexer::getInstance())->getCommandEntity()->attachListeners();

    title.play();
    clck.restart();

    /* Set btntest positions */
    background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188));

    countdownBox->text().setPosition((SCN_WIDTH / 3 + 128) / 2 + 18, (SCN_HEIGHT / 3 + 96) / 2 + 6);
    playerBox->text().setPosition((SCN_WIDTH / 3 + 128) / 2 - 18, (SCN_HEIGHT / 3 + 96) / 2 - 24);

    vesselOneBtn->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) + 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT / 2 - 32);
    vesselTwoBtn->sprite().setPosition((SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) - 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT / 2 - 32);

    vesselOneCircleSGO->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2 + 64), SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 - 32);
    vesselTwoCircleSGO->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2) - 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 - 32);

    deityVitalityBtn->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) + 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT / 2 + 64);
    deityDemiseBtn->sprite().setPosition((SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) - 64, SCN_HEIGHT/ 2 - CLASS_BTN_HEIGHT / 2 + 64);

    deityVitalityCircleSGO->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2) + 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 + 64);
    deityDemiseCircleSGO->sprite().setPosition((SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2) - 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 + 64  );


    //background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188));
    height = MAX_SCROLL;
    cur_movement = 0;
    speed = 70; //Chris, this changes the initial speed then it will be halved as asked.
    total_movement = 0;
    height_mov = 0;
    /* Set the active view */
    updateMainView(viewMain);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::update(sf::Time t)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Chris Klassen and Michael Chimick
--
-- PROGRAMMER: Alex Lam, Chris Klassen, Michael Chimick and Melvin Loho, Jeff Bayntun, Manuel Gonzales
--
-- INTERFACE: void ClientLobbyScene::update(sf::Time t)
--
-- RETURNS: void
--
-- NOTES:
-- Updates buttons
-- Updates timer if countdown is ongoing
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::update(sf::Time t)
{
    if(fake_lobby)
    {
        countdownBox->setText("Match in Progress.  Please wait until current round finishes.");
        return;
    }
    vesselOneBtn->update(t);
    vesselTwoBtn->update(t);
    deityVitalityBtn->update(t);
    deityDemiseBtn->update(t);
    leaveBtn->update(t);

    if(timego && currentTime > 0)
    {
        currentTime -= t.asSeconds();
    }

    if(total_movement < MAX_SCROLL) // total_movement = total movement
    {
      if(height_mov < height/2) //cur_movement = current pixel/time , height = total movement
      {
        cur_movement = t.asSeconds() * speed;
        height_mov += t.asSeconds() * speed;
        total_movement += cur_movement;
        background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188) + total_movement);
      }
      else
      {
        height_mov = 0;
        height = height/2;
        speed = speed/1.5;
      }
    }

    if(currScrollHeight < MAX_SCROLL * 100 / 6)
    {
        sf::Time scrollTime = clck.getElapsedTime();
        currScrollHeight = scrollTime.asMilliseconds();

    }

    //background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188));// + currScrollHeight * 6 / 100);

    deityVitalitySGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H + total_movement);
    deityDemiseSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H + total_movement);

    playerTwoSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6) - 48, SCN_HEIGHT / 3 - 48 - VESSEL_ART_H + total_movement);
    playerThreeSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6) + 48, SCN_HEIGHT / 3 - 48 - VESSEL_ART_H + total_movement);
    playerFourSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - 128 - VESSEL_ART_H + total_movement);

    playerTwoShadowSGO->sprite().setPosition((SCN_WIDTH / 2) - 50, SCN_HEIGHT / 3 - (VESSEL_ART_H / 3) - 58 + total_movement);
    playerThreeShadowSGO->sprite().setPosition((SCN_WIDTH / 2) + 46, SCN_HEIGHT / 3 - (VESSEL_ART_H / 3) - 58 + total_movement);
    playerFourShadowSGO->sprite().setPosition((SCN_WIDTH / 2) - 2, SCN_HEIGHT / 3 - (VESSEL_ART_H / 3) - 138 + total_movement);


    vesselOneSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H +total_movement);
    vesselTwoSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H +total_movement);

    vesselShadowSGO->sprite().setPosition((SCN_WIDTH / 2) - 2, SCN_HEIGHT / 3 - (VESSEL_ART_H / 3) - 10 + total_movement);

    if (timego)
    {
        countdownBox->setText(std::to_string((int)currentTime) + " SECONDS UNTIL THE MATCH" );
    }

    playerBox->setText(std::to_string(playerCount) + " PLAYER(S)");
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::processEvents(sf::Event& e)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: void ClientLobbyScene::processEvents(sf::Event& e)
--
-- RETURNS: void
--
-- NOTES:
-- Processes network messages
-- Either shuts down/ starts countdown
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::processEvents(sf::Event& e)
{
    Scene::processEvents(e);

    if (e.type == sf::Event::Closed)
	{
	    ((ClientMux*)NetworkEntityMultiplexer::getInstance())->shutdown();
		AppWindow::getInstance().close();
	}

    countdownBox->process(e);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::draw()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Chris Klassen and Michael Chimick
--
-- PROGRAMMER: Alex Lam, Chris Klassen, Michael Chimick and Melvin Loho
--
-- INTERFACE: void ClientLobbyScene::draw()
--
-- RETURNS: void
--
-- NOTES:
-- Renders the buttons, textboxes and sprites
-- Creates border around currently selected buttons
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear();

    window.setView(viewMain);

    renderer.begin();

    //Background has to go first
    renderer.draw(background);

    // draw the objects
    renderer.draw(background);
    renderer.draw(vesselOneBtn);
    renderer.draw(vesselTwoBtn);
    renderer.draw(deityVitalityBtn);
    renderer.draw(deityDemiseBtn);
    renderer.draw(leaveBtn);
    renderer.draw(countdownBox);
    renderer.draw(playerBox);

    if(deityChoice == 1)
    {
      renderer.draw(deityVitalityCircleSGO);
      renderer.draw(deityVitalitySGO);
    }

    renderer.draw(vesselShadowSGO);

    if(deityChoice == 2)
    {
        renderer.draw(deityDemiseCircleSGO);
        renderer.draw(deityDemiseSGO);
    }
    if(vesselChoice == 1)
    {
        renderer.draw(vesselOneSGO);
        renderer.draw(vesselOneCircleSGO);
    }

    if(vesselChoice == 2)
    {
        renderer.draw(vesselTwoSGO);
        renderer.draw(vesselTwoCircleSGO);
    }

    // Draw additional players
    switch(playerCount)
    {
        case 4:
            renderer.draw(playerFourShadowSGO);
            renderer.draw(playerFourSGO);
        case 3:
            renderer.draw(playerThreeShadowSGO);
            renderer.draw(playerThreeSGO);
        case 2:
            renderer.draw(playerTwoShadowSGO);
            renderer.draw(playerTwoSGO);
        default:
            break;
    }

    renderer.end();

    window.display();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::onLeaveClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::onLeaveClick()
--
-- RETURNS: void
--
-- NOTES:
-- TODO: Add networking logic for leaving a lobby
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::onLeaveClick()
{
    AppWindow::getInstance().removeScene(1);

    AppWindow::getInstance().addScene(new MainMenuScene());
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::onVesselOneClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::onVesselOneClick()
--
-- RETURNS: void
--
-- NOTES:
-- Sets vessel choice to Vessel 1
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::onVesselOneClick()
{
    vesselChoice = 1;
    cout << "Vessel 1 clicked" << endl;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::onVesselTwoClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::onVesselTwoClick()
--
-- RETURNS: void
--
-- NOTES:
-- Sets vessel choice to Vessel 2
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::onVesselTwoClick()
{
    vesselChoice = 2;
    cout << "Vessel 2 clicked" << endl;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::ondeityVitalityClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::ondeityVitalityClick()
--
-- RETURNS: void
--
-- NOTES:
-- Sets vessel choice to Deity 1
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::ondeityVitalityClick()
{
    deityChoice = 1;
    cout << "Deity 1 clicked" << endl;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::ondeityDemiseClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::ondeityDemiseClick()
--
-- RETURNS: void
--
-- NOTES:
-- Sets vessel choice to Deity 2
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::ondeityDemiseClick()
{
    deityChoice = 2;
    cout << "Deity 2 clicked" << endl;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::updateMainView(sf::View& v)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::updateMainView(sf::View& v)
--            v = main view
-- RETURNS: void
--
-- NOTES:
-- Sets zoom
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();

	//needs to be 3X scale eventually
	 v.zoom(0.33);

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::startTimer(int remainingTime)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: void ClientLobbyScene::startTimer(int remainingTime)
--            remainingTime = the remainder time before the game starts
--
-- RETURNS: void
--
-- NOTES:
-- Starts timer
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::startTimer(int remainingTime)
{
    timego = true;
    currentTime = remainingTime;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::stopTimer(int remainingTime)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: void ClientLobbyScene::stopTimer(int remainingTime)
--
-- RETURNS: void
--
-- NOTES:
-- Stops timer
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::stopTimer(int remainingTime)
{
    timego = false;
    currentTime = remainingTime;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::updatePlayerCount(int numPlayers)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: void ClientLobbyScene::updatePlayerCount(int numPlayers)
--
-- RETURNS: void
--
-- NOTES:
-- Updates player count
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::updatePlayerCount(int numPlayers)
{
    playerCount = numPlayers;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: PlayerLobbyChoices *ClientLobbyScene::getSelections()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: PlayerLobbyChoices *ClientLobbyScene::getSelections()
--
-- RETURNS: void
--
-- NOTES:
-- Get choices from lobby
----------------------------------------------------------------------------------------------------------------------*/
PlayerLobbyChoices *ClientLobbyScene::getSelections()
{
    playerSelections.vesselChoice = vesselChoice;
    playerSelections.deityChoice = deityChoice;

    return &playerSelections;
}
