/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ClientLobbyScene.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--
-- DATE: April 7, 2015
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--             Chris Klassen
--
-- NOTES:
--     This file contains the function implementation of the scoreboard scene for the client.
----------------------------------------------------------------------------------------------------------------------*/

#include "ClientScoreboardScene.h"
#include <iostream>
#include <string>
#include <SFML/System/Time.hpp>
#include "Entities/ClientMux.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;

float ClientScoreboardScene::currentTime;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ClientScoreboardScene
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--             Chris Klassen
--
-- INTERFACE: ClientScoreboardScene::ClientScoreboardScene() : renderer(AppWindow::getInstance(), 48400)
--
-- RETURNS: void
--
-- NOTES:
--     Constructor for the ClientScoreboardScene class
----------------------------------------------------------------------------------------------------------------------*/
ClientScoreboardScene::ClientScoreboardScene() : renderer(AppWindow::getInstance(), 48400)
{
    currentTime = SCORE_COUNTDOWN;

    /* Get texture assets */

    SCORE_ELEMENTS[0] = (char *)"NAME\0";
    SCORE_ELEMENTS[1] = (char *)"ROLE\0";
    SCORE_ELEMENTS[2] = (char *)"SCORE\0";

    data_received = (Player*) malloc(sizeof(Player) * 12);

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/scoreboard-background.png"));

    /*Init artwork*/

    background = new SGO(*Manager::TextureManager::get(backgroundImg));

    sf::Font *font = new sf::Font();
    font->loadFromFile("Assets/Fonts/hud.ttf");

    for (int i = 0; i < SCORE_COLS; i++)
    {
        scoreboard[0][i].text().setScale(SCALE, SCALE);
        scoreboard[0][i].text().move(SCORE_X + (i * OFFSET_X), SCORE_Y);
        scoreboard[0][i].toggleSelected(false);
        scoreboard[0][i].text().setFont(*font);

        scoreboard[0][i].setText(SCORE_ELEMENTS[i]);
    }

    for (int rows = 1; rows < SCORE_ROWS; rows++)
    {
        for (int cols = 0; cols < SCORE_COLS; cols++)
        {
            scoreboard[rows][cols].text().setScale(SCALE, SCALE);
            scoreboard[rows][cols].text().move(SCORE_X + (cols * OFFSET_X), SCORE_Y + (rows * OFFSET_Y));
            scoreboard[rows][cols].toggleSelected(false);
            scoreboard[rows][cols].text().setFont(*font);
        }
    }

    countdownBox = new GUI::TextBox();
    countdownBox->text().setScale(SCALE, SCALE);
    countdownBox->text().move(C_BOX_X + 90, C_BOX_Y + 50);
    countdownBox->toggleSelected(false);
    countdownBox->text().setFont(*font);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ~ClientScoreboardScene
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: ClientScoreboardScene::~ClientScoreboardScene()
--
-- RETURNS: void
--
-- NOTES:
--     Destructor for the ClientScoreboardScene class
----------------------------------------------------------------------------------------------------------------------*/
ClientScoreboardScene::~ClientScoreboardScene()
{
    delete background;
    delete gameScene;
    delete clientMux;
    delete countdownBox;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: onLoad
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void ClientScoreboardScene::onLoad()
--
-- RETURNS: void
--
-- NOTES:
--     Function to be called when the scene is loaded
----------------------------------------------------------------------------------------------------------------------*/
void ClientScoreboardScene::onLoad()
{
    currentTime = SCORE_COUNTDOWN;

    background->sprite().setPosition(SCREEN_WIDTH/3,SCREEN_HEIGHT/3);
    setScoreboard(data_received);

    /* Set the active view */
    updateMainView(viewMain);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: update
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void ClientScoreboardScene::update(sf::Time t)
--                sf::Time t // time elapsed since object created
--
-- RETURNS: void
--
-- NOTES:
--     Function to be called every tick of the scene
----------------------------------------------------------------------------------------------------------------------*/
void ClientScoreboardScene::update(sf::Time t)
{
    for (int rows = 0; rows < SCORE_ROWS; rows++)
    {
        for (int cols = 0; cols < SCORE_COLS; cols++)
        {
            scoreboard[rows][cols].update(t);
        }
    }

    if(currentTime > 0)
    {
        currentTime -= t.asSeconds();
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: processEvents
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void ClientScoreboardScene::processEvents(sf::Event& e)
--                sf::Event& e // event to be processed
--
-- RETURNS: void
--
-- NOTES:
--     Checks all the class entities for open events and calls processing
----------------------------------------------------------------------------------------------------------------------*/
void ClientScoreboardScene::processEvents(sf::Event& e)
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
-- FUNCTION: draw
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void ClientScoreboardScene::draw()
--
-- RETURNS: void
--
-- NOTES:
--     Draws the scene on the screen
----------------------------------------------------------------------------------------------------------------------*/
void ClientScoreboardScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear();

    window.setView(viewMain);

    renderer.begin();

    // draw the objects
    renderer.draw(*background);

    for (int rows = 0; rows < SCORE_ROWS; rows++)
    {
        for (int cols = 0; cols < SCORE_COLS; cols++)
        {
            renderer.draw(scoreboard[rows][cols]);
        }
    }

    countdownBox->setText(std::to_string((int)currentTime) + "s" );
    renderer.draw(*countdownBox);

    renderer.end();

    window.display();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: updateMainView
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void ClientScoreboardScene::updateMainView(sf::View& v)
--                sf::View& v // the current program view
--
-- RETURNS: void
--
-- NOTES:
--     Updates the program view with the class scene
----------------------------------------------------------------------------------------------------------------------*/
void ClientScoreboardScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();

	//needs to be 3X scale eventually
	v.zoom(SCREEN_SCALE);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getInstance
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: ClientScoreboardScene * ClientScoreboardScene::getInstance()
--
-- RETURNS: ClientScoreboardScene * // a new ClientScoreboardScene object
--
-- NOTES:
--     Returns a new scene object
----------------------------------------------------------------------------------------------------------------------*/
ClientScoreboardScene * ClientScoreboardScene::getInstance()
{
    static ClientScoreboardScene * scene = new ClientScoreboardScene();
    return scene;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setScoreboard
--
-- DATE: April 7, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Michael Chimick
--
-- PROGRAMMER: Michael Chimick, Manuel Gonzales
--
-- INTERFACE: void ClientScoreboardScene::setScoreboard(Player* players)
--                Player* players // the players from the last round
--
-- RETURNS: void
--
-- NOTES:
--     Extracts the player values and fills the scoreboard
----------------------------------------------------------------------------------------------------------------------*/
void ClientScoreboardScene::setScoreboard(Player* players)
{
    for (int rows = 1; rows < SCORE_ROWS; rows++)
    {
        if(players[rows-1].type > -1)
        {
            //strcpy(players[rows - 1].name, "bob\0"); // this is to test the name spacing
            scoreboard[rows][0].setText(players[rows - 1].name);
            switch(players[rows - 1].type)
            {
                case 0:
                    scoreboard[rows][1].setText("Vessel");
                    break;

                case 1:
                    scoreboard[rows][1].setText("Ghost");
                    break;

                case 2:
                    scoreboard[rows][1].setText("Deity");
                    break;
            }
            scoreboard[rows][2].setText(std::to_string(players[rows - 1].score));
        }
    }
}
