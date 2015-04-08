#include "AppWindow.h"

using namespace Marx;

/******************************************************************************
*	FUNCTION: getInstance
*
*	DATE: March 10, 2015
*
*	DESIGNER: Melvin Loho
*
*	PROGRAMMER: Melvin Loho
*
*	INTERFACE: AppWindow& AppWindow::getInstance()
*
*	RETURNS:
*		The static AppWindow object.
*
*	NOTES:
*		Returns the static AppWindow object.
*
******************************************************************************/
AppWindow& AppWindow::getInstance()
{
	static AppWindow app;

	return app;
}

/******************************************************************************
*	FUNCTION: getCurrentView
*
*	DATE: March 10, 2015
*
*	DESIGNER: Melvin Loho
*
*	PROGRAMMER: Melvin Loho
*
*	INTERFACE: sf::View getCurrentView()
*
*	RETURNS:
*		sf::View - the up to date view of the AppWindow
*
*	NOTES:
*		Gets the up to date view of the AppWindow
*
******************************************************************************/
sf::View AppWindow::getCurrentView() const
{
	sf::Vector2u size = getSize();
	return sf::View(
		sf::Vector2f(size.x * 0.5f, size.y * 0.5f),
		sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y))
		);
}

/******************************************************************************
*	FUNCTION: getMousePositionRelativeToWindowAndView
*
*	DATE: March 10, 2015
*
*	DESIGNER: Melvin Loho
*
*	PROGRAMMER: Melvin Loho
*
*	INTERFACE: sf::Vector2f AppWindow::getMousePositionRelativeToWindowAndView(const sf::View &view) const
*
*	RETURNS:
*		sf::Vector2f - the mouse position
*
*	NOTES:
*		Gets the mouse position relative to the window and view
*
******************************************************************************/
sf::Vector2f AppWindow::getMousePositionRelativeToWindowAndView(const sf::View &view) const {
	return mapPixelToCoords(sf::Mouse::getPosition(*this), view);
}

/******************************************************************************
*	FUNCTION: addScene
*
*	DATE: February 15, 2015
*
*	REVISIONS: February 16, 2015 - Changed to use a map for easier access.
*
*	DESIGNER: Marc Vouve
* 			  Melvin Loho
*
*	PROGRAMMER: Marc Vouve
*				Marc Rafanan
*
*	INTERFACE: bool addScene(string name, Scene scene)
*
*	PARAMETERS:
*		scene	- scene to be added to the appwindow
*
*
*	RETURNS:
*		void
*
*	NOTES:
*		Adds a scene to the app
*
******************************************************************************/
int AppWindow::addScene(Scene *scene)
{
	this->scene.emplace_back(scene);

	this->scene.back()->onLoad();

	return 0;
}


/******************************************************************************
*	FUNCTION: removeScene
*
*	DATE: February 15, 2015
*
*	REVISIONS: February 16, 2016
*
*	DESIGNER: Marc Vouve
*			  Melvin Loho
*
*	PROGRAMMER: Marc Rafanan
*				Marc Vouve
*
*	INTERFACE: void removeScene(std::string name)
*		std::string name: The name of the scene to remove
*
*	PARAMETERS:
*		index	- index of the scene to be removed
*
*	RETURNS:
*		void
*
*	NOTES:
*		Removes a scene from the scenes vector in the app window
*
******************************************************************************/
void AppWindow::removeScene(int id)
{
	auto removedScene =
		this->scene.erase(this->scene.begin() + id);

	(*removedScene)->unLoad();
}

/******************************************************************************
*	FUNCTION: run
*
*	DATE: February 15, 2015
*
*	REVISIONS: February 16, 2016
*
*	DESIGNER: Marc Vouve
*			  Melvin Loho
*
*	PROGRAMMER: Marc Vouve
*
*	INTERFACE: void removeScene(std::string name)
*		std::string name: The name of the scene to remove
*
*	PARAMETERS:
*		index	- index of the scene to be removed
*
*	RETURNS:
*		void
*
*	NOTES:
*		Removes a scene from the scenes vector in the app window
*
******************************************************************************/
void AppWindow::run()
{
	if (!isRunning)
	{
		isRunning = true;

		sf::Clock clock;
		sf::Event event;

		// LOOP
		while (isOpen())
		{
			// process networking messages
			Networking::handleSessionMessages();

			// TIME UPDATES
			m_elapsedTime = clock.restart();
			m_timeSinceLastUpdate += m_elapsedTime;

			// CHECK FOR EVENTS
			while (pollEvent(event))
			{
				scene.back()->processEvents(event);
			}

			// TIME PER FRAME CONTROLLED LOOP
			while (m_timeSinceLastUpdate > m_timePerFrame)
			{
				m_timeSinceLastUpdate -= m_timePerFrame;

				for (Scene* s : scene)
					s->update(m_timePerFrame);
			}

			// RENDER
			for (Scene* s : scene)
				s->draw();
		}

		isRunning = false;
	}
}

/******************************************************************************
*	FUNCTION: AppWindow
*
*	DATE: February 15, 2015
*
*	REVISIONS: February 16, 2016
*
*	DESIGNER: Marc Vouve
*			  Melvin Loho
*
*	PROGRAMMER: Marc Vouve
*			    Melvin Loho
*
*	INTERFACE: AppWindow::AppWindow()
*
*	PARAMETERS:
*
*	RETURNS:
*
*	NOTES:
*		Creates the game window.
*
******************************************************************************/
AppWindow::AppWindow() : sf::RenderWindow(sf::VideoMode(1366, 768), "Sojourn", sf::Style::Close, sf::ContextSettings(0,0,0))
{
	Scene *s = new Scene;
	scene.emplace_back(s);
	m_timePerFrame = sf::seconds(1.f / 60);
}
