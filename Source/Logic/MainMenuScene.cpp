#include "../AppWindow.h"
#include "../Network/Client.h"
#include "Entities/ClientMux.h"
#include "MainMenuScene.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

using Networking::NetworkEntityMultiplexer;
using Networking::Client;

MainMenuScene * MainMenuScene::getInstance()
{
    static MainMenuScene * scene = new MainMenuScene();
    return scene;
}

MainMenuScene::MainMenuScene() : renderer(AppWindow::getInstance(), 48400)
{
    // trying to create a background
    // backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Multimedia/Assets/button.png"));
    // background = new SGO(*Manager::TextureManager::get(backgroundImg));

    backgroundImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/couch.jpg"));
    background = new SGO(*Manager::TextureManager::get(backgroundImg));
    background->sprite().setScale(5, 5);

    serverLbl   = new GUI::Label( background, std::string("Server:") );
    portLbl     = new GUI::Label( background, std::string("Port:" ) );
    nicknameLbl = new GUI::Label( background, std::string("Nickname:" ) );
    sf::Font *arial = new sf::Font();
    arial->loadFromFile("Assets/Fonts/arial.ttf");

    textBoxes[ SERVER_TXT ]   = new GUI::TextBox( nextTextBox, this );
    textBoxes[ PORT_TXT ]     = new GUI::TextBox( nextTextBox, this );
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
    connectImg = Manager::TextureManager::store(Manager::TextureManager::load("Assets/connect_btn.png"));
    connectBtn = new GUI::Button(*Manager::TextureManager::get(connectImg), sf::Vector2f(BTN_SIZE, BTN_SIZE), viewMain, onClick);
}

MainMenuScene::~MainMenuScene()
{
    delete textBoxes[ SERVER_TXT ];
    delete textBoxes[ PORT_TXT ];
    delete textBoxes[ NICKNAME_TXT ];

    // delete serverLbl;
    // delete portLbl;
    // delete nicknameLbl;

    delete connectBtn;
}

void MainMenuScene::onLoad()
{
    /* Set button positions */
    serverLbl->text().setPosition(0, 0);
    portLbl->text().setPosition(0, 25);
    nicknameLbl->text().setPosition(0, 50);

    textBoxes[ SERVER_TXT ]->text().move(50, 0);
    textBoxes[ PORT_TXT ]->text().move(50, 15);
    textBoxes[ NICKNAME_TXT ]->text().move(50, 30);

    connectBtn->sprite().setPosition(100, 200);

    /* Set the active view */
    updateMainView(viewMain);
}

void MainMenuScene::update(sf::Time t)
{
    connectBtn->update(t);
}

void MainMenuScene::processEvents(sf::Event& e)
{
    Scene::processEvents(e);
    textBoxes[ curTextBox ]->process(e);
}

void MainMenuScene::draw()
{
    AppWindow& window = AppWindow::getInstance();

    window.clear(sf::Color::Blue);

    window.setView(viewMain);

    renderer.begin();

    renderer.draw( background, true );

    // draw the objects
    renderer.draw( serverLbl );
    renderer.draw( portLbl );
    renderer.draw( nicknameLbl );

    for( int i = 0; i < TEXT_BOXES; ++i )
        renderer.draw( textBoxes[ i ] );

    renderer.draw( connectBtn );

    renderer.end();

    window.display();
}

void MainMenuScene::onClick()
{
    GameScene* gameScene = new GameScene();
    ClientLobbyScene* lobbyScene = new ClientLobbyScene();
    ClientMux* clientmux = new ClientMux(gameScene,lobbyScene);
    NetworkEntityMultiplexer::setInstance(clientmux);

    Client* client = new Client();
    short port = atoi( MainMenuScene::getInstance()->textBoxes[ PORT_TXT ]->getText().c_str() );
    client->connect( (char *)MainMenuScene::getInstance()->textBoxes[ SERVER_TXT ]->getText().c_str(), port);

    printf("connected\n");
}

void MainMenuScene::updateMainView(sf::View& v)
{
    v = AppWindow::getInstance().getCurrentView();
}

void nextTextBox( void * data )
{
    MainMenuScene * thiz = (MainMenuScene *) data;
    ++thiz->curTextBox;
    thiz->curTextBox %= TEXT_BOXES;
    thiz->textBoxes[ thiz->curTextBox ]->toggleSelected(true);
}
