
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

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
CreditScene * CreditScene::getInstance()
{
    static CreditScene * scene = new CreditScene(MainMenuScene::getInstance());
    return scene;
}

/******************************************************************************
*	FUNCTION:   The constructor for the credit scene
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*               Jonathan Chu
*
*	PARAMETERS: 
*
*	RETURNS:    void
*
*	NOTES:
******************************************************************************/
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

    credits_msc = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Sound/music.wav"));
    music = Manager::MusicManager::get(credits_msc);
	
	lord_msc = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Sound/lorde.wav"));
    lord = Manager::MusicManager::get(lord_msc);
}

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
CreditScene::~CreditScene()
{
    delete backBtn;
    delete background;
    delete creditText;

    // delete serverLbl;
    // delete portLbl;
    // delete nicknameLbl;
}

/******************************************************************************
*	FUNCTION:   loads the objects
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*               Jonathan Chu
*
*	INTERFACE:  void CreditScene::onLoad()
*
*	PARAMETERS: 
*
*	RETURNS:    void
*
*	NOTES:
******************************************************************************/
void CreditScene::onLoad()
{
    /* Set button positions */

    backBtn->sprite().setPosition(350, 550);
    creditText->sprite().move(0, AppWindow::getInstance().getSize().y);

    /* Set the active view */
    updateMainView(viewMain);

    music->play();
	lord->play();
}

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
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

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void CreditScene::processEvents(sf::Event& e)
{
    if (e.type == sf::Event::Closed)
    {
        AppWindow::getInstance().close();
    }
}

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
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

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void CreditScene::onClick()
{
    AppWindow::getInstance().removeScene(1);

    AppWindow::getInstance().addScene(CreditScene::getInstance()->mainmenu);
}

/******************************************************************************
*	FUNCTION:
*
*	DATE:
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER:
*
*	PROGRAMMER:
*
*	INTERFACE:
*
*	PARAMETERS:
*
*	RETURNS: void
*
*	NOTES:
******************************************************************************/
void CreditScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
}
