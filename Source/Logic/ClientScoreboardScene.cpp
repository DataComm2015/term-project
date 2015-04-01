#include "ClientScoreboardScene.h"
#include <iostream>
#include <SFML/System/Time.hpp>
#include "Entities/ClientMux.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;

sf::Clock ClientScoreboardScene::clock;
float ClientScoreboardScene::currentTime;


ClientScoreboardScene::ClientScoreboardScene() : renderer(AppWindow::getInstance(), 48400)
{
    /* Get texture assets */
    
    SCORE_ELEMENTS[0] = (char *)"NAME\0";
    SCORE_ELEMENTS[1] = (char *)"ROLE\0";
    SCORE_ELEMENTS[2] = (char *)"SCORE\0";

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/Art/GUI/Menu/scoreboard-background.png"));

    /*Init artwork*/

    background = new SGO(*Manager::TextureManager::get(backgroundImg));

    sf::Font *arial = new sf::Font();
    arial->loadFromFile("Assets/Fonts/arial.ttf");

    for (int i = 0; i < SCORE_COLS; i++)
    {
        scoreboard[0][i].text().setScale(TEXTBOX_SCALE, TEXTBOX_SCALE);
        scoreboard[0][i].text().move(SCORE_X + (i * OFFSET_X), SCORE_Y);
        scoreboard[0][i].toggleSelected(false);
        scoreboard[0][i].text().setFont(*arial);
        
        scoreboard[0][i].setText(SCORE_ELEMENTS[i]);
    }

    for (int rows = 1; rows < SCORE_ROWS; rows++)
    {
        for (int cols = 0; cols < SCORE_COLS; cols++)
        {
            scoreboard[rows][cols].text().setScale(TEXTBOX_SCALE, TEXTBOX_SCALE);
            scoreboard[rows][cols].text().move(SCORE_X + (cols * OFFSET_X), SCORE_Y + (rows * OFFSET_Y));
            scoreboard[rows][cols].toggleSelected(false);
            scoreboard[rows][cols].text().setFont(*arial);
        }
    }
    
    countdownBox = new GUI::TextBox();
    countdownBox->text().setScale(TEXTBOX_SCALE, TEXTBOX_SCALE);
    countdownBox->text().move(C_BOX_X, C_BOX_Y);
    countdownBox->toggleSelected(false);
    countdownBox->text().setFont(*arial);
}

ClientScoreboardScene::~ClientScoreboardScene()
{
    delete background;
    delete gameScene;
    delete clientMux;
    delete countdownBox;
}

void ClientScoreboardScene::onLoad()
{
    background->sprite().setPosition(0,0);

    /* Set the active view */
    updateMainView(viewMain);
}

void ClientScoreboardScene::update(sf::Time t)
{
    for (int rows = 0; rows < SCORE_ROWS; rows++)
    {
        for (int cols = 0; cols < SCORE_COLS; cols++)
        {
            scoreboard[rows][cols].update(t);
        }
    }
}

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

void ClientScoreboardScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear();

    window.setView(viewMain);

    renderer.begin();

    // draw the objects
    renderer.draw(*background);

    /* this block shows what is needed to set the scoreboard */
    char ** newBoard[SCORE_ROWS - 1]; // should be 12
    for (int rows = 0; rows < (SCORE_ROWS - 1); rows++)
    {
        // all arrays should at least have a "\0"
        newBoard[rows] = new char*[SCORE_COLS]; // should be 3
        newBoard[rows][0] = new char[8]; // 8 is an arbitrariy number
        strcpy(newBoard[rows][0], "bob\0");
        newBoard[rows][1] = new char[8];
        strcpy(newBoard[rows][1], "vessel\0");
        newBoard[rows][2] = new char[8];
        strcpy(newBoard[rows][2], "1000\0");
    }
    
    setScoreboard(newBoard);
    /* end block */
    
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

void ClientScoreboardScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();

	//needs to be 3X scale eventually
	v.zoom(0.66);
}

ClientScoreboardScene * ClientScoreboardScene::getInstance()
{
    static ClientScoreboardScene * scene = new ClientScoreboardScene();
    return scene;
}

void ClientScoreboardScene::setScoreboard(char ** newBoard[])
{
    for (int rows = 1; rows < SCORE_ROWS; rows++)
    {
        scoreboard[rows][0].setText(newBoard[rows - 1][0]);
        scoreboard[rows][1].setText(newBoard[rows - 1][1]);
        scoreboard[rows][2].setText(newBoard[rows - 1][2]);
    }
}
