#include "ClientLobbyScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

ClientLobbyScene::ClientLobbyScene() : renderer(AppWindow::getInstance(), 48400)
{
    // trying to create a background
    // backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    // background = new SGO(*Manager::TextureManager::get(backgroundImg));

    /* Get texture assets */
    // as art assets are created for these, add them
    vesselOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    vesselTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));

    aspectOneImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    aspectTwoImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    aspectThreeImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));

    readyImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));

    /* Initialize buttons */
    vesselOneBtn = new GUI::Button(*Manager::TextureManager::get(vesselOneImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onclick);
    vesselTwoBtn = new GUI::Button(*Manager::TextureManager::get(vesselTwoImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onclick);

    aspectOneBtn = new GUI::Button(*Manager::TextureManager::get(aspectOneImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onclick);
    aspectTwoBtn = new GUI::Button(*Manager::TextureManager::get(aspectTwoImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onclick);
    aspectThreeBtn = new GUI::Button(*Manager::TextureManager::get(aspectThreeImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onclick);

    readyBtn = new GUI::Button(*Manager::TextureManager::get(readyImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onclick);
}

ClientLobbyScene::~ClientLobbyScene()
{
    delete vesselOneBtn;
    delete vesselTwoBtn;

    delete aspectOneBtn;
    delete aspectTwoBtn;
    delete aspectThreeBtn;

    delete readyBtn;
}

void ClientLobbyScene::onLoad()
{
    /* Set button positions */
    vesselOneBtn->operator()().setPosition(0, 0);
    vesselTwoBtn->operator()().setPosition(1 + BTN_SIZE, 0);
    
    aspectOneBtn->operator()().setPosition(0, 1 + BTN_SIZE);
    aspectTwoBtn->operator()().setPosition(1 + BTN_SIZE, 1 + BTN_SIZE);
    aspectThreeBtn->operator()().setPosition(2 + BTN_SIZE, 1 + BTN_SIZE);

    readyBtn->operator()().setPosition(0, 2 + BTN_SIZE + BTN_SIZE);

    vesselOneBtn->toggleEnabled(true);
    vesselTwoBtn->toggleEnabled(false);

    aspectOneBtn->toggleEnabled(true);
    aspectTwoBtn->toggleEnabled(false);
    aspectThreeBtn->toggleEnabled(false);

    readyBtn->toggleEnabled(false);

    /* Set the active view */
    updateMainView(viewMain);
}

void ClientLobbyScene::update(sf::Time)
{
    //
}

void ClientLobbyScene::processEvents(sf::Event& e)
{
    //
}

void ClientLobbyScene::draw()
{
    AppWindow& window = AppWindow::getInstance();
    
    window.clear();

    window.setView(viewMain);

    renderer.begin();

    // draw the objects
    renderer.draw(*vesselOneBtn);
    renderer.draw(*vesselTwoBtn);
    renderer.draw(*aspectOneBtn);
    renderer.draw(*aspectTwoBtn);
    renderer.draw(*aspectThreeBtn);
    renderer.draw(*readyBtn);

    renderer.end();

    window.display();
}

void ClientLobbyScene::onclick()
{
    // temp onclick function
    cout << "Button clicked" << endl;
}

void ClientLobbyScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
}
