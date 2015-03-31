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

    circle = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/boxOutline.png"));

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/lobby-background.png"));

    vesselOneArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/vessel-one.png"));
    vesselTwoArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/vessel-two.png"));

    vesselOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-btn.png"));
    vesselTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));

    aspectOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/warrior-btn.png"));
    aspectTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));

    leaveImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/shaman-btn.png"));

    /* Initialize buttons */
    vesselOneBtn = new GUI::Button(*Manager::TextureManager::get(vesselOneImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onVesselOneClick);

    vesselTwoBtn = new GUI::Button(*Manager::TextureManager::get(vesselTwoImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onVesselTwoClick);

    aspectOneBtn = new GUI::Button(*Manager::TextureManager::get(aspectOneImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onDeityOneClick);
    aspectTwoBtn = new GUI::Button(*Manager::TextureManager::get(aspectTwoImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onDeityTwoClick);

    leaveBtn     = new GUI::Button(*Manager::TextureManager::get(leaveImg), sf::Vector2f(CLASS_BTN_WIDTH, CLASS_BTN_HEIGHT), viewMain, onLeaveClick);


    /*Init artwork*/
    vesselOneSGO = new SGO(*Manager::TextureManager::get(vesselOneArt));
    vesselTwoSGO = new SGO(*Manager::TextureManager::get(vesselTwoArt));

    vesselOneCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    vesselTwoCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    deityOneCircleSGO = new SGO(*Manager::TextureManager::get(circle));
    deityTwoCircleSGO = new SGO(*Manager::TextureManager::get(circle));

    background = new SGO(*Manager::TextureManager::get(backgroundImg));

    sf::Font *arial = new sf::Font();
    arial->loadFromFile("Assets/Fonts/arial.ttf");


    countdownBox = new GUI::TextBox();
    countdownBox->text().setScale(1, 1);
    //countdownBox->text().move(30, 5);
    countdownBox->toggleSelected(false);
    countdownBox->text().setFont(*arial);

    playerBox = new GUI::TextBox();
    playerBox->text().setScale(1, 1);
    //playerBox->text().move(30, 20);
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

    delete aspectOneBtn;
    delete aspectTwoBtn;

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
    /* Set btntest positions */
    background->sprite().setPosition(0,0);

    countdownBox->text().setPosition((SCN_WIDTH*1/5)/2,SCN_HEIGHT*1/10);
    playerBox->text().setPosition((SCN_WIDTH*1/5)/2,SCN_HEIGHT*1/10 + SCN_HEIGHT*1/30);

    vesselOneBtn->sprite().setPosition( (0 + SCN_WIDTH/3 - CLASS_BTN_WIDTH/2), SCN_HEIGHT/2 - CLASS_BTN_HEIGHT/2);
    vesselTwoBtn->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH/3 - CLASS_BTN_WIDTH/2) , SCN_HEIGHT/2 - CLASS_BTN_HEIGHT/2);

    vesselOneCircleSGO->sprite().setPosition( (0 + SCN_WIDTH/3 - CLASS_BTN_WIDTH_B/2), SCN_HEIGHT/2 - CLASS_BTN_HEIGHT_B/2);
    vesselTwoCircleSGO->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH/3 - CLASS_BTN_WIDTH_B/2) , SCN_HEIGHT/2 - CLASS_BTN_HEIGHT_B/2);

    aspectOneBtn->sprite().setPosition((0 + SCN_WIDTH/3 - CLASS_BTN_WIDTH/2)          , SCN_HEIGHT/2 + SCN_HEIGHT/4 - CLASS_BTN_HEIGHT_B/2);
    aspectTwoBtn->sprite().setPosition((SCN_WIDTH - SCN_WIDTH/3 - CLASS_BTN_WIDTH/2)  , SCN_HEIGHT/2 + SCN_HEIGHT/4 - CLASS_BTN_HEIGHT_B/2);

    deityOneCircleSGO->sprite().setPosition( (0 + SCN_WIDTH/3 - CLASS_BTN_WIDTH_B/2)          , SCN_HEIGHT/2 + SCN_HEIGHT/4 - CLASS_BTN_HEIGHT_B/2);
    deityTwoCircleSGO->sprite().setPosition((SCN_WIDTH - SCN_WIDTH/3 - CLASS_BTN_WIDTH_B/2)  , SCN_HEIGHT/2 + SCN_HEIGHT/4 - CLASS_BTN_HEIGHT_B/2 );

    leaveBtn->sprite().setPosition(SCN_WIDTH*.66+CLASS_BTN_WIDTH_B*3, SCN_HEIGHT * 0.20);

    vesselOneSGO->sprite().setPosition(SCN_WIDTH/2 - VESSEL_ART_WH/2,SCN_HEIGHT- VESSEL_ART_WH);
    vesselTwoSGO->sprite().setPosition(SCN_WIDTH/2 - VESSEL_ART_WH/2,SCN_HEIGHT- VESSEL_ART_WH);

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
    aspectOneBtn->update(t);
    aspectTwoBtn->update(t);
    leaveBtn->update(t);

    if(timego && currentTime > 0)
    {
        currentTime -= t.asSeconds();
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
    renderer.draw(*aspectOneBtn);
    renderer.draw(*aspectTwoBtn);
    renderer.draw(*leaveBtn);
    renderer.draw(*countdownBox);
    renderer.draw(*playerBox);

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

    if(deityChoice == 1)
    {
        renderer.draw(*deityOneCircleSGO);
    }

    if(deityChoice == 2)
    {
        renderer.draw(*deityTwoCircleSGO);
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
	v.zoom(0.66);

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
