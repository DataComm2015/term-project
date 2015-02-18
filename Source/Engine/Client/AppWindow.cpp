#include "AppWindow.h"

namespace Marx
{
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
	void AppWindow::addScene(Scene* scene)
	{
		this->scene.emplace_back(scene);
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
	*							std::string name: The name of the scene to remove
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
		this->scene.erase(this->scene.begin() + id);
	}

	/******************************************************************************
	*	FUNCTION: AppWindow
	*
	*	DATE: February 15, 2015
	*
	*	REVISIONS: (Date and Description)
	*
	*	DESIGNER: Marc Rafanan
	*
	*	PROGRAMMER: Marc Rafanan
	*
	*	INTERFACE: AppWindow()
	*
	*	PARAMETERS:
	*		void
	*
	*	RETURNS:
	*		void
	*
	*	NOTES:
	*		Constructor for the AppWindow Class. Initializes the main game window.
	*
	******************************************************************************/
	AppWindow::AppWindow()
	{
		this->create(sf::VideoMode(800, 600), "The Game"); // Temp name
	}


	


	void AppWindow::run()
	{
		sf::Clock clock;
		sf::Event event;
		if(!isRunning)
		{
			isRunning == true;

			while(isOpen())
			{
				elapsedTime = clock.restart();
				timeSinceLastUpdate += elapsedTime;

				// check window events
				while(pollEvent(event))	// inherited from sf::RenderWindow
				{
					// window event handler
				}

				while(timeSinceLastUpdate > timePerFrame)
				{
					timeSinceLastUpdate -= timePerFrame;
					for(std::vector<Marx::Scene*>::iterator it = scene.begin(); it != scene.end(); ++it )
					{
						//*(it)->processEvents();
					}
				}

				for(std::vector<Marx::Scene*>::iterator it = scene.begin(); it != scene.end(); ++it )
				{
					//*(it)->draw();
				}
			}
		}
	}
}


// Test to see if the window is opening
int main()
{
	Marx::AppWindow window;
	window.run();
	
	return 0;
}