
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
    //set scale to (3, 3) and the image will fit in perfectly with borders 
    background->sprite().setScale(3, 3);

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
    creditText->sprite().move(0, AppWindow::getInstance().getSize().y);

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
    else
    {
      cout << "HELLO -> the credits are done" << endl;
      CreditScene::onClick();
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

    window.clear();

    window.setView(viewMain);

    renderer.begin();

    renderer.draw( background );

    // draw the objects
    renderer.draw( creditText );

    //renderer.draw( backBtn );

    renderer.end();

    window.display();
}

void CreditScene::onClick()
{
    AppWindow::getInstance().removeScene(1);

    AppWindow::getInstance().addScene(CreditScene::getInstance()->mainmenu);
}

void CreditScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
}
