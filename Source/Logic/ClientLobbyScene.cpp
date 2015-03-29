#include "ClientLobbyScene.h"
#include <iostream>
#include <SFML/System/Time.hpp>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;

int ClientLobbyScene::vesselChoice;
int ClientLobbyScene::deityChoice;
sf::Clock ClientLobbyScene::clck;
bool ClientLobbyScene::timego;
int ClientLobbyScene::maxTime;
int ClientLobbyScene::currentTime;


ClientLobbyScene::ClientLobbyScene() : renderer(AppWindow::getInstance(), 48400)
{
    /* Get texture assets */
    // as art assets are created for these, add them

    vesselChoice = 1;
    deityChoice = 1;
    maxTime = COUNTDOWN;
    currentTime = COUNTDOWN;

    circle = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/circleOutline.png"));

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/lobby-background.jpg"));

    vesselOneArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/vessel-one.png"));
    vesselTwoArt = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/vessel-two.png"));

    vesselOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/btnTest.png"));
    vesselTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/btnTest.png"));

    aspectOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/btnTest.png"));
    aspectTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/btnTest.png"));

    leaveImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/btnTest.png"));

    /* Initialize buttons */
    vesselOneBtn = new GUI::Button(*Manager::TextureManager::get(vesselOneImg), sf::Vector2f(BTN_WIDTH, BTN_HEIGHT), viewMain, onVesselOneClick);
    vesselTwoBtn = new GUI::Button(*Manager::TextureManager::get(vesselTwoImg), sf::Vector2f(BTN_WIDTH, BTN_HEIGHT), viewMain, onVesselTwoClick);

    aspectOneBtn = new GUI::Button(*Manager::TextureManager::get(aspectOneImg), sf::Vector2f(BTN_WIDTH, BTN_HEIGHT), viewMain, onDeityOneClick);
    aspectTwoBtn = new GUI::Button(*Manager::TextureManager::get(aspectTwoImg), sf::Vector2f(BTN_WIDTH, BTN_HEIGHT), viewMain, onDeityTwoClick);

    leaveBtn     = new GUI::Button(*Manager::TextureManager::get(leaveImg), sf::Vector2f(BTN_WIDTH, BTN_HEIGHT), viewMain, onLeaveClick);

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
    countdownBox->text().move(5, 5);
    countdownBox->toggleSelected(false);
    countdownBox->text().setFont(*arial);

    playerBox = new GUI::TextBox();
    playerBox->text().setScale(1, 1);
    playerBox->text().move(5, 20);
    playerBox->toggleSelected(false);
    playerBox->text().setFont(*arial);

}

ClientLobbyScene::~ClientLobbyScene()
{
    delete vesselOneBtn;
    delete vesselTwoBtn;

    delete aspectOneBtn;
    delete aspectTwoBtn;

    delete leaveBtn;
}

void ClientLobbyScene::onLoad()
{
    /* Set btntest positions */
    vesselOneBtn->sprite().setPosition( (0 + SCN_WIDTH/4 - BTN_WIDTH/2)         , SCN_HEIGHT/2 - BTN_HEIGHT/2);
    vesselTwoBtn->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH/4 - BTN_WIDTH/2) , SCN_HEIGHT/2 - BTN_HEIGHT/2);

    vesselOneCircleSGO->sprite().setPosition( (0 + SCN_WIDTH/4 - CIRCLE_WH/2)         , SCN_HEIGHT/2 - CIRCLE_WH/2);
    vesselTwoCircleSGO->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH/4 - CIRCLE_WH/2) , SCN_HEIGHT/2 - CIRCLE_WH/2);

    aspectOneBtn->sprite().setPosition((0 + SCN_WIDTH/4 - BTN_WIDTH/2)          , SCN_HEIGHT/2 + SCN_HEIGHT/4 - BTN_HEIGHT/2);
    aspectTwoBtn->sprite().setPosition((SCN_WIDTH - SCN_WIDTH/4 - BTN_WIDTH/2)  , SCN_HEIGHT/2 + SCN_HEIGHT/4 - BTN_HEIGHT/2);

    deityOneCircleSGO->sprite().setPosition( (0 + SCN_WIDTH/4 - CIRCLE_WH/2)         , SCN_HEIGHT/2 + SCN_HEIGHT/4- CIRCLE_WH/2);
    deityTwoCircleSGO->sprite().setPosition( (SCN_WIDTH - SCN_WIDTH/4 - CIRCLE_WH/2) , SCN_HEIGHT/2 + SCN_HEIGHT/4- CIRCLE_WH/2);

    leaveBtn->sprite().setPosition((SCN_WIDTH - BTN_WIDTH), 0);

    vesselOneSGO->sprite().setPosition(SCN_WIDTH/2 - VESSEL_ART_WH/2,0);
    vesselTwoSGO->sprite().setPosition(SCN_WIDTH/2 - VESSEL_ART_WH/2,0);

    background->sprite().setPosition(0,0);

    /* Set the active view */
    updateMainView(viewMain);
}

void ClientLobbyScene::update(sf::Time t)
{
    vesselOneBtn->update(t);
    vesselTwoBtn->update(t);
    aspectOneBtn->update(t);
    aspectTwoBtn->update(t);
    leaveBtn->update(t);
}

void ClientLobbyScene::processEvents(sf::Event& e)
{
    countdownBox->process(e);
}

void ClientLobbyScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear();

    window.setView(viewMain);

    if(timego)
    {
        sf::Time timersa;
        timersa = clck.getElapsedTime();
        float cTime = timersa.asSeconds();
        currentTime = maxTime - cTime;
        if(currentTime == 0)
        {
            timego = false;
            AppWindow::getInstance().removeScene(1);
            AppWindow::getInstance().setVerticalSyncEnabled(true);
            AppWindow::getInstance().addScene(gameScene);
            AppWindow::getInstance().run();
        }
    }


    renderer.begin();

    countdownBox->setText(std::to_string(currentTime) + "s" );
    playerBox->setText("1 player");

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

void ClientLobbyScene::onLeaveClick()
{

    //TEMPORARY LOCATION FOR CLOCk
    clck.restart();
    timego = true;

    cout << "Button clicked" << endl;
}

void ClientLobbyScene::onVesselOneClick()
{
    vesselChoice = 1;
    cout << "Vessel 1 clicked" << endl;
}

void ClientLobbyScene::onVesselTwoClick()
{
    vesselChoice = 2;
    cout << "Vessel 2 clicked" << endl;
}

void ClientLobbyScene::onDeityOneClick()
{
    deityChoice = 1;
    cout << "Deity 1 clicked" << endl;
}

void ClientLobbyScene::onDeityTwoClick()
{
    deityChoice = 2;
    cout << "Deity 2 clicked" << endl;
}

void ClientLobbyScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
}

int ClientLobbyScene::getDeityChoice()
{
    return deityChoice;
}

int ClientLobbyScene::getVesselChoice()
{
    return vesselChoice;
}
