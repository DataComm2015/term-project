///////////////////////////////////////////////////////////////////////////////
//
//  Author: Melvin Loho
//
//  This file demonstrates how the API made so far by the Game Engine team
//  and the Multimedia Team could be used. It will continually be updated
//  as more features are created.
//
//  WARNING: some things may not be working yet
//  while others might just be there for placeholders.
//
//  This list will keep track of the areas that are fully functional:
//  - None so far, oh joy...
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  I will also use this as an alpha testing ground for our API
//  to see if there are anything missing or
//  if something's not working the way it should.
//
//  Here's the awesome TODO list:
//  - AppWindow needs a getCurrentView() function
//    which returns its current view (appropriate positioning and scaling).
//  - Have a way to remove the scene from itself using getWindow().removeScene(ME)
//    figure out what ME should be, below you can find my proposal.
//  - Resource Managers for fonts?
//
///////////////////////////////////////////////////////////////////////////////

//> In a separate scene file
// Note that a scene made for content can just be a header file

#include "AppWindow.h"
#include "Engine/Scene.h"
#include "Engine/TextureManager.h"
#include "Multimedia/graphics/Renderer.h"
#include "Multimedia/graphics/object/BGO.h"
#include "Multimedia/graphics/object/SGO.h"
#include "Multimedia/graphics/object/TGO.h"

class StartScreen : public Marx::Scene
{
public:
	// Constructors should be used to initialize things only once on scene creation
	StartScreen() : Scene()
		, renderer(AppWindow::getInstance(), 4242)
	{
		// Load and store calls to a resource manager should be done only once, but for demonstration purposes..
		texture_1 = Manager::TextureManager::store(
			Manager::TextureManager::load("Multimedia/Assets/Art/Misc/placeholder.png")
			);

		texture_2 = Manager::TextureManager::store(
			Manager::TextureManager::load("Multimedia/Assets/Art/Player/Idle/vessel-idle.png")
			);

		// configure the sprite

		//background().setTexture(*Manager::TextureManager::get(texture_1));
		sgo().setTexture(*Manager::TextureManager::get(texture_2));

		v = new Vessel(0,NULL,0,0);



		// might want to have another resource manager for fonts...
		font.loadFromFile("Multimedia/Assets/Fonts/arial.ttf");

		// configure the text this doesn't compile :/
		//welcomeText().setFont(font);
		//welcomeText().setCharacterSize(30);
		//welcomeText().setString("Welcome to Spectre");
	}

	// Destructors are... obvious
	~StartScreen()
	{}

	// onload's should be used to reinitialize/reset stuff when the scene is loaded or REloaded
	void onLoad() override
	{
		view_hud = view_main = AppWindow::getInstance().getCurrentView();
	}

	// unload's should be used to stop/kill/terminate stuff when the scene leaves, like stopping a playing music.
	void unLoad() override
	{
		// not really useful right now so we don't have to override this
	}

	// Hey look! It's the WndProc of SFML!!
	void processEvents(sf::Event& event) override
	{
		// YESS so many switch case statements!!
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			v->move(event.key);
			break;

		case sf::Event::KeyReleased:
			v->stop();
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				// TODO Can't suicide yet...
				// getWindow().removeScene(this->getID()); // SUICIDE
				break;
			}
			break;

		case sf::Event::Closed:
			AppWindow::getInstance().close();
			break;

		case sf::Event::Resized:
			view_hud = view_main = AppWindow::getInstance().getCurrentView();
			break;
		}
	}

	// Update callback, do logical stuff here
	void update(sf::Time t) override
	{

		/* This code moves the background but keeps the vessel centered */
		view_main.move(v->getXSpeed(), v->getYSpeed());
		sgo().setPosition(view_main.getCenter()); //*/

		/* This code moves the vessel around but keeps the screen centered
		sgo().setPosition(v->getXPosition(), v->getYPosition());
		//*/
	}

	// Render callback, render stuff here
	void draw() override
	{
		AppWindow::getInstance().clear(); // necessary at top

		renderer.resetStats(); // necessary before rendering unless you don't care about the stats

		AppWindow::getInstance().setView(view_main); // change view to view_main for stuff like: entities, players, map, world...

		renderer.begin(); // always begin before rendering anything

		renderer.states.blendMode = sf::BlendAdd; // pointless in this case, but useful in others

		renderer.draw(background);

		renderer.end(); // always end when you're done rendering or want to start fresh again

		renderer.begin();
		renderer.draw(sgo);
		renderer.end();

		AppWindow::getInstance().setView(view_hud); // change view to view_hud for HUD stuff

		renderer.begin();

		renderer.draw(welcomeText);

		renderer.end();

		AppWindow::getInstance().display(); // necessary at bottom
	}

private:
	sf::View view_hud, view_main;

	Renderer renderer;

	id_resource texture_1, texture_2;
	SGO background;

	SGO sgo;
	Vessel* v;

	sf::Font font;
	TGO welcomeText;
};

/*
//> In the main file
#include "AppWindow.h"
// include the separate scene file

int main()
{
	StartScreen scene1;

	AppWindow::getInstance().addScene(&scene1);

	AppWindow::getInstance().run();

	return 0;
}*/
