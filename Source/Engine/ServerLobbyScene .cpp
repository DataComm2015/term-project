#include "ServerLobbyScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

ServerLobbyScene::ServerLobbyScene() : renderer(AppWindow.getInstance(), 48400)
{
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

    /* Set the active view */
    updateMainView(viewMain);
}

ServerLobbyScene::~ServerLobbyScene()
{
    delete vesselOneBtn;
	delete vesselTwoBtn;

    delete aspectOneBtn;
    delete aspectTwoBtn;
    delete aspectThreeBtn;

    delete readyBtn;
}

void ServerLobbyScene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void ServerLobbyScene::processEvents(sf::Event& e)
{
	
}

void ServerLobbyScene::draw()
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
}

void onclick()
{
    // temp onclick function
}
