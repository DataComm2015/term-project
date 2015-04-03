#include "ClientLobbyScene.h"
#include <iostream>
#include <SFML/System/Time.hpp>
#include "Entities/ClientMux.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;

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
-- DESIGNER: Calvin Rempel, Alex Lam and Michael Chimick
--
-- PROGRAMMER: Calvin Rempel, Alex Lam and Michael Chimick
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
ClientLobbyScene::ClientLobbyScene() : renderer(AppWindow::getInstance(), 48400)
{
    /* Get texture assets */
    // as art assets are created for these, add them

    playerCount = 0;
    vesselChoice = 1;
    deityChoice = 1;
    timego = false;
    click = 0;

    circle = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/selected.png"));

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/lobby.png"));

    vesselOneArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-img.png"));
    vesselTwoArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-img.png"));

    deityOneArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/vitality-img.png"));
    deityTwoArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/demise-img.png"));

    vesselOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-btn.png"));
    vesselTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));

    deityOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/vitality-btn.png"));
    deityTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/demise-btn.png"));

    leaveImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));


    /* Initialize buttons */
    vesselOneBtn = new GUI::Button(*Manager::TextureManager::get(vesselOneImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onVesselOneClick);

    vesselTwoBtn = new GUI::Button(*Manager::TextureManager::get(vesselTwoImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onVesselTwoClick);

    deityOneBtn = new GUI::Button(*Manager::TextureManager::get(deityOneImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onDeityOneClick);
    deityTwoBtn = new GUI::Button(*Manager::TextureManager::get(deityTwoImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onDeityTwoClick);

    leaveBtn     = new GUI::Button(*Manager::TextureManager::get(leaveImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onLeaveClick);

    /*Init artwork*/
    vesselOneSGO = new SGO(*Manager::TextureManager::get(vesselOneArt));
    vesselTwoSGO = new SGO(*Manager::TextureManager::get(vesselTwoArt));

    deityOneSGO = new SGO(*Manager::TextureManager::get(deityOneArt));
    deityTwoSGO = new SGO(*Manager::TextureManager::get(deityTwoArt));

    vesselOneCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    vesselTwoCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    deityOneCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    deityTwoCircleSGO = new SGO(*Manager::TextureManager::get(circle));

    background = new SGO(*Manager::TextureManager::get(backgroundImg));

    sf::Font *arial = new sf::Font();
    arial->loadFromFile("Assets/Fonts/arial.ttf");


    countdownBox = new GUI::TextBox(NULL,NULL);
    countdownBox->text().setScale(0.66, 0.66);
    countdownBox->toggleSelected(false);
    countdownBox->text().setFont(*arial);

    playerBox = new GUI::TextBox(NULL,NULL);
    playerBox->text().setScale(0.66, 0.66);
    playerBox->toggleSelected(false);
    playerBox->text().setFont(*arial);
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

    delete deityOneBtn;
    delete deityTwoBtn;

    delete leaveBtn;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::onLoad()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
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
    clck.restart();

    /* Set btntest positions */
    background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188));

    countdownBox->text().setPosition((SCN_WIDTH / 3 + 128) / 2, (SCN_HEIGHT / 3 + 64) / 2);
    playerBox->text().setPosition((SCN_WIDTH / 3 + 128) / 2, (SCN_HEIGHT / 3 + 96) / 2);

    vesselOneBtn->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) + 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT / 2 - 32);
    vesselTwoBtn->sprite().setPosition((SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) - 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT / 2 - 32);

    vesselOneCircleSGO->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2 + 64), SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 - 32);
    vesselTwoCircleSGO->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2) - 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 - 32);

    deityOneBtn->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) + 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT / 2 + 64);
    deityTwoBtn->sprite().setPosition((SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH / 2) - 64, SCN_HEIGHT/ 2 - CLASS_BTN_HEIGHT / 2 + 64);

    deityOneCircleSGO->sprite().setPosition((SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2) + 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 + 64);
    deityTwoCircleSGO->sprite().setPosition((SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH_B / 2) - 64, SCN_HEIGHT / 2 - CLASS_BTN_HEIGHT_B / 2 + 64  );

    leaveBtn->sprite().setPosition(SCN_WIDTH - SCN_WIDTH / 3 - CLASS_BTN_WIDTH - 8, SCN_HEIGHT / 3 + 8);

    //background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188));
    height = MAX_SCROLL;
    cur_movement = 0;
    speed = 35; //Chris, this changes the initial speed then it will be halved as asked.
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
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::update(sf::Time t)
--
-- RETURNS: void
--
-- NOTES:
-- updates buttons
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::update(sf::Time t)
{
    vesselOneBtn->update(t);
    vesselTwoBtn->update(t);
    deityOneBtn->update(t);
    deityTwoBtn->update(t);
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
        speed = speed/2;
      }
    }
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
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::draw()
--
-- RETURNS: void
--
-- NOTES:
-- Renders the buttons, textboxes and sprites
-- Creates border around currently selected buttons
-- Updates timer if countdown is ongoing
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear();

    window.setView(viewMain);

    renderer.begin();

    //Background has to go first

    if(currScrollHeight < MAX_SCROLL * 100 / 6)
    {
        sf::Time scrollTime = clck.getElapsedTime();
        currScrollHeight = scrollTime.asMilliseconds();

    }

    //background->sprite().setPosition(SCN_WIDTH / 3, (SCN_HEIGHT / 3 - 188));// + currScrollHeight * 6 / 100);

    deityOneSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H + total_movement);
    deityTwoSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H + total_movement);

    vesselOneSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H +total_movement);
    vesselTwoSGO->sprite().setPosition((SCN_WIDTH / 2) - (VESSEL_ART_W / 6), SCN_HEIGHT / 3 - VESSEL_ART_H +total_movement);


    renderer.draw(*background);

    if (timego)
    {
        countdownBox->setText(std::to_string((int)currentTime) + "s" );
    }

    playerBox->setText(std::to_string(playerCount) + " player(s)");

    // draw the objects
    renderer.draw(*background);
    renderer.draw(*vesselOneBtn);
    renderer.draw(*vesselTwoBtn);
    renderer.draw(*deityOneBtn);
    renderer.draw(*deityTwoBtn);
    renderer.draw(*leaveBtn);
    renderer.draw(*countdownBox);
    renderer.draw(*playerBox);

    if(deityChoice == 1)
    {
        renderer.draw(*deityOneCircleSGO);
        renderer.draw(*deityOneSGO);

    }

    if(deityChoice == 2)
    {
        renderer.draw(*deityTwoCircleSGO);
        renderer.draw(*deityTwoSGO);
    }
    if(vesselChoice == 1)
    {
        renderer.draw(*vesselOneSGO);
        renderer.draw(*vesselOneCircleSGO);
    }

    if(vesselChoice == 2)
    {
        renderer.draw(*vesselTwoSGO);
        renderer.draw(*vesselTwoCircleSGO);
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

    AppWindow::getInstance().run();
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
-- FUNCTION: void ClientLobbyScene::onDeityOneClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::onDeityOneClick()
--
-- RETURNS: void
--
-- NOTES:
-- Sets vessel choice to Deity 1
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::onDeityOneClick()
{
    deityChoice = 1;
    cout << "Deity 1 clicked" << endl;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void ClientLobbyScene::onDeityTwoClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam and Michael Chimick
--
-- PROGRAMMER: Alex Lam and Michael Chimick
--
-- INTERFACE: void ClientLobbyScene::onDeityTwoClick()
--
-- RETURNS: void
--
-- NOTES:
-- Sets vessel choice to Deity 2
----------------------------------------------------------------------------------------------------------------------*/
void ClientLobbyScene::onDeityTwoClick()
{
    deityChoice = 2;
    cout << "Deity 2 clicked" << endl;
}

void ClientLobbyScene::easterEggClick()
{
      if(click<18)
      {
        click++;
      }
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
