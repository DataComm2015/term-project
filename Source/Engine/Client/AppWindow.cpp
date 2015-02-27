#include "AppWindow.h"


int main(void)
{
	Marx::AppWindow window;
    window.run();

return 0;
}

using namespace Marx;
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
int AppWindow::addScene(Scene &scene)
{
	this->scene.emplace_back(scene);

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
	this->scene.erase(this->scene.begin() + id);
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
	sf::Clock clock;
	sf::Event event;
	if(!isRunning)
	{
		isRunning == true;

		while(isOpen())
		{
			nextUpdate = clock.getElapsedTime() + timePerFrame;
			// check window events
			while(pollEvent(event))	// inherited from sf::RenderWindow
			{
				// if the window is being closed deal with it here.
				if (event.type == sf::Event::Closed)
                	close();
				scene.back().processEvents(event);
			}
			while(clock.getElapsedTime() < nextUpdate)
			{
				for(std::vector<Scene>::iterator it = scene.begin(); it != scene.end(); ++it )
				{
					it->update(clock.getElapsedTime());
					printf("Update");
				}
			}

			for(std::vector<Scene>::iterator it = scene.begin(); it != scene.end(); ++it )
			{
				it->draw();
				printf("draw\n");
			}
		}
	}
}


// Test to see if the window is opening
