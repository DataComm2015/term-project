/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: MainMenuScene.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:      
--
-- DATE: March 30, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER:
--
-- PROGRAMMER:  Chris Klassen
--
-- NOTES:
--        
----------------------------------------------------------------------------------------------------------------------*/


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

bool MainMenuScene::connectFailed;
GameScene *MainMenuScene::gameScene = NULL;

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
-- PROGRAMMER: Alex Lam, Manuel Gonzales, Chris Klassen and Georgi Hristov
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

    connectFailed = false;

    client = new Client();
    lobbyScene = new ClientLobbyScene();
    scoreScene = new ClientScoreboardScene();
    clientmux = new ClientMux(lobbyScene, scoreScene);
    NetworkEntityMultiplexer::setInstance(clientmux);

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/lobby.png"));
    textBackgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/text-box.png"));
    textBackgroundBoxImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/text-box-outline.png"));
    bannerImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/logo.png"));

    menuMsc = Manager::MusicManager::store(Manager::MusicManager::load("Assets/Music/music_intro_or_lobby.ogg"));


    music = Manager::MusicManager::get(menuMsc);

    background = new SGO(*Manager::TextureManager::get(backgroundImg));
    banner = new SGO(*Manager::TextureManager::get(bannerImg));

    //background = new SGO(*Manager::TextureManager::get(backgroundImg));
    background->sprite().setScale(1, 1);

    sf::Font *font = new sf::Font();
    font->loadFromFile("Assets/Fonts/hud.ttf");

    textBoxes[ SERVER_TXT ]   = new GUI::TextBox( nextTextBox, this, 16 );
    textBoxes[ SERVER_TXT ]   ->setText("localhost");
    textBoxes[ PORT_TXT ]     = new GUI::TextBox( nextTextBox, this, 4 );
    textBoxes[ PORT_TXT ]     ->setText("7000");
    textBoxes[ NICKNAME_TXT ] = new GUI::TextBox( nextTextBox, this, 16 );

    curTextBox = 0;
    textBoxes[ SERVER_TXT ]  ->toggleSelected(true);
    textBoxes[ PORT_TXT ]    ->toggleSelected(false);
    textBoxes[ NICKNAME_TXT ]->toggleSelected(false);

    textBoxes[ SERVER_TXT ]->text().setFont(*font);
    textBoxes[ PORT_TXT ]->text().setFont(*font);
    textBoxes[ NICKNAME_TXT ]->text().setFont(*font);

    serverLbl   = new GUI::Label( background, std::string("SERVER:") );
    portLbl     = new GUI::Label( background, std::string("PORT:") );
    nicknameLbl = new GUI::Label( background, std::string("NAME:") );

    serverLbl     ->text().setFont(*font);
    portLbl       ->text().setFont(*font);
    nicknameLbl   ->text().setFont(*font);

    serverLbl     ->text().setScale(FONT_SCALE, FONT_SCALE);
    portLbl       ->text().setScale(FONT_SCALE, FONT_SCALE);
    nicknameLbl   ->text().setScale(FONT_SCALE, FONT_SCALE);

    textBoxes[ SERVER_TXT ]  ->text().setScale(FONT_SCALE, FONT_SCALE);
    textBoxes[ PORT_TXT ]    ->text().setScale(FONT_SCALE, FONT_SCALE);
    textBoxes[ NICKNAME_TXT ]->text().setScale(FONT_SCALE, FONT_SCALE);

    connectFailedText = new GUI::TextBox( NULL, this );
    connectFailedText ->setText(connectFailErr);
    connectFailedText ->text().setFont(*font);
    connectFailedText ->text().setScale(FONT_SCALE, FONT_SCALE);


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
    delete name_sent;
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
-- PROGRAMMER: Alex Lam, Chris Klassen, Manuel Gonzales and Georgi Hristov
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
    banner->sprite().setPosition(SCN_WIDTH / 2 - BANNER_W / 2 - 80, SCN_HEIGHT / 3 + 4);

    background->sprite().setPosition(SCN_WIDTH / 3, SCN_HEIGHT / 3 - 188);

    serverTextBackground  ->sprite().setPosition(textw, text1_h);
    portTextBackground    ->sprite().setPosition(textw, text2_h);
    nicknameTextBackground->sprite().setPosition(textw, text3_h);

    serverTextBackgroundBox->sprite().setPosition(text_b_w + 2, text1_b_h);
    portTextBackgroundBox->sprite().setPosition(text_b_w + 2, text2_b_h);
    nicknameTextBackgroundBox->sprite().setPosition(text_b_w + 2, text3_b_h);

    serverLbl   ->text().setPosition((textw / 2 - TEXT_BOX_W/4)* 1.2, (text1_h / 2)* 1.19);
    portLbl     ->text().setPosition((textw / 2 - TEXT_BOX_W/4)* 1.2 + 9, (text2_h / 2)* 1.19);
    nicknameLbl ->text().setPosition((textw / 2 - TEXT_BOX_W/4)* 1.2 + 8, (text3_h / 2)* 1.19);

    textBoxes[ SERVER_TXT ]   ->text().setPosition((textw / 2 + 5)* 1.175, (text1_h / 2)* 1.19);
    textBoxes[ PORT_TXT ]     ->text().setPosition((textw / 2 + 5)* 1.175, (text2_h / 2)* 1.19);
    textBoxes[ NICKNAME_TXT ] ->text().setPosition((textw / 2 + 5)* 1.175, (text3_h / 2)* 1.19);

    connectFailedText         ->text().setPosition((textw / 2 + 5)* FONT_OFFSET, (text3_h/3)* 1.19);

    connectBtn->sprite().setPosition(SCN_WIDTH/2 - CLASS_BTN_WIDTH / 2 - CLASS_BTN_WIDTH + 120, SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*4);
    creditBtn ->sprite().setPosition(SCN_WIDTH/2 + CLASS_BTN_WIDTH / 2 - CLASS_BTN_WIDTH/2 + 120, SCN_HEIGHT/3 + 90 + (TEXT_BOX_H + 2)*4);

    curTextBox = 0;
    textBoxes[ SERVER_TXT ]->toggleSelected(true);
    textBoxes[ PORT_TXT ]->toggleSelected(false);
    textBoxes[ NICKNAME_TXT ]->toggleSelected(false);

    music->play();

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

    if (e.type == sf::Event::Closed)
    {
        AppWindow::getInstance().close();
    }

    textBoxes[ curTextBox ]->process(e);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void MainMenuScene::draw()
--
-- DATE: Mar 30, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Alex Lam, Chris Klassen, Manuel Gonzales and Georgi Hristov
--
-- PROGRAMMER: Alex Lam, Chris Klassen, Manuel Gonzales and Georgi Hristov
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

    window.clear();

    window.setView(viewMain);

    renderer.begin();

    renderer.draw( background );

    // draw the objects
    renderer.draw(banner);
    renderer.draw(serverTextBackground);
    renderer.draw(portTextBackground);
    renderer.draw(nicknameTextBackground);

    renderer.draw( serverLbl );
    renderer.draw( portLbl );
    renderer.draw( nicknameLbl );

    if(textBoxes[SERVER_TXT]->getSelected())
    {
      renderer.draw(serverTextBackgroundBox);
    }
    if(textBoxes[PORT_TXT]->getSelected())
    {
      renderer.draw(portTextBackgroundBox);
    }
    if(textBoxes[NICKNAME_TXT]->getSelected())
    {
      renderer.draw(nicknameTextBackgroundBox);
    }

    if(connectFailed)
    {
      renderer.draw(connectFailedText);
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
      if (strlen(nickname_text) == 0)
      {
         connectFailed = true;
         return;
      }

      MainMenuScene::getInstance()->clientmux->message.type = (int)PlayerCommandMsgType::SERVER_SELECTED_NICKNAME;
      MainMenuScene::getInstance()->clientmux->message.len = strlen(nickname_text);
      //clientmux->message.data = (char*)"TEST";
      MainMenuScene::getInstance()->name_sent = new char[16];
      memcpy(MainMenuScene::getInstance()->name_sent, nickname_text, strlen(nickname_text) + 1);
      MainMenuScene::getInstance()->clientmux->message.data = MainMenuScene::getInstance()->name_sent;

      short port = atoi( MainMenuScene::getInstance()->textBoxes[ PORT_TXT ]->getText().c_str() );
      if (MainMenuScene::getInstance()->client->connect( (char *)MainMenuScene::getInstance()->textBoxes[ SERVER_TXT ]->getText().c_str(), port) <= 0)
      {
          printf("not connected\n");
          connectFailed = true;
          // Show Error Message
      }
      else
      {
          printf("connected\n");
      }
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
    v.zoom(0.33);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: GameScene* MainMenuScene::getGameScene()
--
-- DATE: April 5, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: GameScene* MainMenuScene::getGameScene()
--
-- RETURNS: the active GameScene (creates a new one if none is active)
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
GameScene *MainMenuScene::getGameScene()
{
    if (gameScene == NULL)
    {
        gameScene = new GameScene();
    }

    return gameScene;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: void clearGameScene()
--
-- DATE: April 5, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: void clearGameScene()
--
-- RETURNS: void
--
-- NOTES: deletes the current game scene
----------------------------------------------------------------------------------------------------------------------*/
void MainMenuScene::clearGameScene()
{
    delete gameScene;
    gameScene = NULL;
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
