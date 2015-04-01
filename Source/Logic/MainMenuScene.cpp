#include "../AppWindow.h"
#include "../Network/Message.h"
#include "../Network/Client.h"
#include "NetworkEntityPairs.h"
#include "Entities/ClientMux.h"
#include "MainMenuScene.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;
using Networking::Client;
using Networking::Message;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MainMenuScene * MainMenuScene::getInstance()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: MainMenuScene * MainMenuScene::getInstance()
--
-- RETURNS: current scene instance
--
-- NOTES:
-- returns scene
----------------------------------------------------------------------------------------------------------------------*/
MainMenuScene * MainMenuScene::getInstance()
{
    static MainMenuScene * scene = new MainMenuScene();
    return scene;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MainMenuScene::MainMenuScene() : renderer(AppWindow::getInstance(), 48400)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: MainMenuScene::MainMenuScene() : renderer(AppWindow::getInstance(), 48400)
--
-- RETURNS: void
--
-- NOTES:
-- Initalizes GUI
-- Loads in artwork
-- Creates background, buttons and textboxes
----------------------------------------------------------------------------------------------------------------------*/
MainMenuScene::MainMenuScene() : renderer(AppWindow::getInstance(), 48400)
{
    // trying to create a background
    // backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    // background = new SGO(*Manager::TextureManager::get(backgroundImg));

    client = new Client();
    gameScene = new GameScene();
    lobbyScene = new ClientLobbyScene();
    scoreScene = new ClientScoreboardScene();
    clientmux = new ClientMux(gameScene,lobbyScene, scoreScene);
    NetworkEntityMultiplexer::setInstance(clientmux);

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/couch.jpg"));
    textBackgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/textBackground.png"));
    textBackgroundBoxImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/textBackgroundBox.png"));
    bannerImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Menu/vessel-one.png"));

    background = new SGO(*Manager::TextureManager::get(backgroundImg));
    banner = new SGO(*Manager::TextureManager::get(bannerImg));

    background = new SGO(*Manager::TextureManager::get(backgroundImg));
    background->sprite().setScale(5, 5);

    serverLbl   = new GUI::Label( background, std::string("Server:") );
    portLbl     = new GUI::Label( background, std::string("Port:" ) );
    nicknameLbl = new GUI::Label( background, std::string("Nickname:" ) );
    sf::Font *arial = new sf::Font();
    arial->loadFromFile("Assets/Fonts/arial.ttf");

    textBoxes[ SERVER_TXT ]   = new GUI::TextBox( nextTextBox, this, 16 );
    textBoxes[ SERVER_TXT ]   ->setText("localhost");
    textBoxes[ PORT_TXT ]     = new GUI::TextBox( nextTextBox, this, 4 );
    textBoxes[ NICKNAME_TXT ] = new GUI::TextBox( nextTextBox, this, 16 );
    textBoxes[ PORT_TXT ]     ->setText("7000");
    textBoxes[ NICKNAME_TXT ] = new GUI::TextBox( nextTextBox, this );

    curTextBox = 0;
    textBoxes[ SERVER_TXT ]->toggleSelected(true);
    textBoxes[ PORT_TXT ]->toggleSelected(false);
    textBoxes[ NICKNAME_TXT ]->toggleSelected(false);

    textBoxes[ SERVER_TXT ]->text().setFont(*arial);
    textBoxes[ PORT_TXT ]->text().setFont(*arial);
    textBoxes[ NICKNAME_TXT ]->text().setFont(*arial);

    /* Get texture assets */
    // as art assets are created for these, add them
    connectImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/connected-btn.png"));
    connectBtn = new GUI::Button(*Manager::TextureManager::get(connectImg), sf::Vector2f(WIDE_BUTTONS_W, WIDE_BUTTONS_H), viewMain, onClick);

    creditImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/credits-btn.png"));
    creditBtn = new GUI::Button(*Manager::TextureManager::get(creditImg), sf::Vector2f(WIDE_BUTTONS_W, WIDE_BUTTONS_H), viewMain, onClickCredit);

    serverTextBackground = new SGO(*Manager::TextureManager::get(textBackgroundImg));
    portTextBackground = new SGO(*Manager::TextureManager::get(textBackgroundImg));
    nicknameTextBackground = new SGO(*Manager::TextureManager::get(textBackgroundImg));

    serverTextBackgroundBox = new SGO(*Manager::TextureManager::get(textBackgroundBoxImg));
    portTextBackgroundBox = new SGO(*Manager::TextureManager::get(textBackgroundBoxImg));
    nicknameTextBackgroundBox = new SGO(*Manager::TextureManager::get(textBackgroundBoxImg));

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MainMenuScene::~MainMenuScene()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: MainMenuScene::~MainMenuScene()
--
-- RETURNS: void
--
-- NOTES:
-- Deconstruts MainMenuScene and cleans up
----------------------------------------------------------------------------------------------------------------------*/
MainMenuScene::~MainMenuScene()
{
    delete textBoxes[ SERVER_TXT ];
    delete textBoxes[ PORT_TXT ];
    delete textBoxes[ NICKNAME_TXT ];

    // delete serverLbl;
    // delete portLbl;
    // delete nicknameLbl;

    delete connectBtn;
    delete creditBtn;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::onLoad()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::onLoad()
--
-- RETURNS: void
--
-- NOTES:
-- Sets position of buttons, textboxes and sprites
-- updates main view
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::onLoad()
{
    /* Set button positions */
    banner->sprite().setPosition(SCN_WIDTH/2 - BANNER_W/2, SCN_HEIGHT/10);

    serverTextBackground  ->sprite().setPosition(textw, text1_h);
    portTextBackground    ->sprite().setPosition(textw, text2_h);
    nicknameTextBackground->sprite().setPosition(textw, text3_h);

    serverTextBackgroundBox->sprite().setPosition(text_b_w, text1_b_h);
    portTextBackgroundBox->sprite().setPosition(text_b_w, text2_b_h);
    nicknameTextBackgroundBox->sprite().setPosition(text_b_w, text3_b_h);

    serverLbl             ->text().setPosition(0, 0);
    portLbl               ->text().setPosition(0, 0);
    nicknameLbl           ->text().setPosition(0, 0);

    textBoxes[ SERVER_TXT ]   ->text().setPosition(textw/2+5, text1_h/2 - 3);
    textBoxes[ PORT_TXT ]     ->text().setPosition(textw/2+5, text2_h/2 - 3);
    textBoxes[ NICKNAME_TXT ] ->text().setPosition(textw/2+5, text3_h/2 - 3);

    connectBtn->sprite().setPosition(SCN_WIDTH/2 - CLASS_BTN_WIDTH * 1.5, SCN_HEIGHT*.75);
    creditBtn->sprite().setPosition(SCN_WIDTH/2 + CLASS_BTN_WIDTH/2, SCN_HEIGHT*.75);

    curTextBox = 0;
    textBoxes[ SERVER_TXT ]->toggleSelected(true);
    textBoxes[ PORT_TXT ]->toggleSelected(false);
    textBoxes[ NICKNAME_TXT ]->toggleSelected(false);

    /* Set the active view */
    updateMainView(viewMain);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::update(sf::Time t)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::update(sf::Time t)
--
-- RETURNS: void
--
-- NOTES:
-- updates buttons
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::update(sf::Time t)
{
    connectBtn->update(t);
    creditBtn->update(t);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::processEvents(sf::Event& e)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::processEvents(sf::Event& e)
--
-- RETURNS: void
--
-- NOTES:
-- Processes event
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::processEvents(sf::Event& e)
{
    Scene::processEvents(e);
    textBoxes[ curTextBox ]->process(e);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::draw()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::draw()
--
-- RETURNS: void
--
-- NOTES:
-- Renders the button, textboxes and sprites.
-- Creates border around the currently selected textbox
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear(sf::Color::Blue);

    window.setView(viewMain);

    renderer.begin();

    renderer.draw( background, true );

    // draw the objects
    renderer.draw(*banner);
    renderer.draw(*serverTextBackground);
    renderer.draw(*portTextBackground);
    renderer.draw(*nicknameTextBackground);

    renderer.draw( serverLbl );
    renderer.draw( portLbl );
    renderer.draw( nicknameLbl );

    if(textBoxes[SERVER_TXT]->getSelected())
    {
      renderer.draw(*serverTextBackgroundBox);
    }
    if(textBoxes[PORT_TXT]->getSelected())
    {
      renderer.draw(*portTextBackgroundBox);
    }
    if(textBoxes[NICKNAME_TXT]->getSelected())
    {
      renderer.draw(*nicknameTextBackgroundBox);
    }


    for( int i = 0; i < TEXT_BOXES; ++i )
        renderer.draw( textBoxes[ i ] );

    renderer.draw( connectBtn );
    renderer.draw( creditBtn );

    renderer.end();

    window.display();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::onClick()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Alex Lam, Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::onClick()
--
-- RETURNS: void
--
-- NOTES:
-- Handles connect button press
-- if port, address, and nickname is empty, it will not continue to the next screen.
-- TODO: Add conditions for empty address and empty username
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::onClick()
{
    int port = atoi(MainMenuScene::getInstance()->textBoxes[ PORT_TXT ]->getText().c_str());
    char* addr = (char*)MainMenuScene::getInstance()->textBoxes[ SERVER_TXT ]->getText().c_str();
    cout << (port == 0) << endl;

    if(port != 0 && 1) //TODO: add check for address filled in
    {
      char* nickname_text = (char *)MainMenuScene::getInstance()->textBoxes[ NICKNAME_TXT ]->getText().c_str();

      MainMenuScene::getInstance()->clientmux->message.type = (int)PlayerCommandMsgType::SERVER_SELECTED_NICKNAME;
      MainMenuScene::getInstance()->clientmux->message.len = strlen(nickname_text);
      //clientmux->message.data = (char*)"TEST";
      char* hello = new char[16];
      memcpy(hello, nickname_text, strlen(nickname_text));
      MainMenuScene::getInstance()->clientmux->message.data = hello;

      short port = atoi( MainMenuScene::getInstance()->textBoxes[ PORT_TXT ]->getText().c_str() );
      if (MainMenuScene::getInstance()->client->connect( (char *)MainMenuScene::getInstance()->textBoxes[ SERVER_TXT ]->getText().c_str(), port) <= 0)
      {
          printf("not connected\n");
          // Show Error Message
      }
      else
      {
         printf("connected\n");  
      }

      delete hello;
    }

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::onClickCredit()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::onClickCredit()
--
-- RETURNS: void
--
-- NOTES:
-- Handles credit button press
-- TODO:call credit scene
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::onClickCredit()
{
    CreditScene* creditscene = new CreditScene(MainMenuScene::getInstance());

    AppWindow::getInstance().removeScene(1);

    AppWindow::getInstance().addScene(creditscene);

    AppWindow::getInstance().run();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::updateMainView(sf::View& v)
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void MainMenuScene::updateMainView(sf::View& v)
--            v = main view
--
-- RETURNS: void
--
-- NOTES:
-- Sets zoom
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
    v.zoom(0.66);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void nextTextBox( void * data )
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Manuel Gonzales and Georgi Hristov
--
-- INTERFACE: void nextTextBox( void * data )
--
-- RETURNS: void
--
-- NOTES:
-- Iterates through the textboxes
----------------------------------------------------------------------------------------------------------------------*/
void nextTextBox( void * data )
{
    MainMenuScene * thiz = (MainMenuScene *) data;
    ++thiz->curTextBox;
    thiz->curTextBox %= TEXT_BOXES;
    thiz->textBoxes[ thiz->curTextBox ]->toggleSelected(true);
}
