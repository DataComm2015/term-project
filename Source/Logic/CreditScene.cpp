
#include "../AppWindow.h"
#include "../Network/Client.h"
#include "Entities/ClientMux.h"
#include "CreditScene.h"
#include <iostream>
#include "MainMenuScene.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

CreditScene * CreditScene::getInstance()
{
    static CreditScene * scene = new CreditScene(MainMenuScene::getInstance());
    return scene;
}

CreditScene::CreditScene(MainMenuScene* mainmen) : renderer(AppWindow::getInstance(), 48400)
{
    // trying to create a background
    // backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    // background = new SGO(*Manager::TextureManager::get(backgroundImg));

    mainmenu = mainmen;
    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/credits-background.png"));
    background = new SGO(*Manager::TextureManager::get(backgroundImg));
    background->sprite().setScale(5, 5);

    creditImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/credits.png"));
    creditText = new SGO(*Manager::TextureManager::get(creditImg));
    creditText->sprite().setScale(3, 3);
    /* Get texture assets */
    // as art assets are created for these, add them
    backImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/connect_btn.png"));
   	backBtn = new GUI::Button(*Manager::TextureManager::get(backImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onClick);

}



CreditScene::~CreditScene()
{
    delete backBtn;
    delete background;
    delete creditText;

    // delete serverLbl;
    // delete portLbl;
    // delete nicknameLbl;
}

void CreditScene::onLoad()
{
    /* Set button positions */

    backBtn->sprite().setPosition(350, 550);

    /* Set the active view */
    updateMainView(viewMain);
}

void CreditScene::update(sf::Time t)
{
    backBtn->update(t);

    if(creditText->sprite().getPosition().y > -2500 )
    {
        creditText->sprite().move(0, -t.asSeconds() * 100);
    }
}

void CreditScene::processEvents(sf::Event& e)
{
    if (e.type == sf::Event::Closed)
    {
        AppWindow::getInstance().close();
    }
}

void CreditScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear(sf::Color::Blue);

    window.setView(viewMain);

    renderer.begin();

    renderer.draw( background, true );

    // draw the objects
    renderer.draw( creditText, true);

    renderer.draw( backBtn );

    renderer.end();

    window.display();
}

void CreditScene::onClick()
{
    AppWindow::getInstance().removeScene(1);

    AppWindow::getInstance().addScene(CreditScene::getInstance()->mainmenu);

    AppWindow::getInstance().run();

}

void CreditScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
}
