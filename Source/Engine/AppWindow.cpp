#include "AppWindow.h"

/******************************************************************************
*	FUNCTION: gameLoop
*
*	DATE: February 15, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: gameLoop()
*
*	PARAMETERS:
*		// void for now
*
*	RETURNS:
*		bool 	- success or failure
*
*	NOTES:
*		The main loop for the game. The game loop processes turns for all of 
*		the scenes. Each scene is loaded into the app window on creation and 
*		will not have a loop of its own for the sake of synchronisation.
*
*		compile with: -lsfml-graphics -lsfml-window -lsfml-system
******************************************************************************/
bool AppWindow::gameLoop()
{
	// Display the window
	this->window.clear();
    this->window.display();
	
	while(this->window.isOpen())
	{
			for(std::vector<Scene*>::iterator it = this->scenes.begin();
				it != this->scenes.end();
				++it)
			{
				//ProcessEvents
				(*it)->events();
				
				//Update
				(*it)->update();
				
				//Draw
				(*it)->draw();
			}
			
	}
	
	return true;
}

/******************************************************************************
*	FUNCTION: addScene
*
*	DATE: February 15, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: bool addScene(Scene scene)
*
*	PARAMETERS:
*		scene	- scene to be added to the appwindow
*
*	RETURNS:
*		int		- scene id
*
*	NOTES:
*		Adds a scene to the app window and returns the scene id.
*
******************************************************************************/
int AppWindow::addScene(Scene* scene)
{
	this->scenes.push_back(scene);
	
	// return id of the scene added. used for removeScene. Either return
	// id after adding or overload == operator for the scene.
	return (this->scenes.size() - 1);
}


/******************************************************************************
*	FUNCTION: removeScene
*
*	DATE: February 15, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: bool removeScene(int index)
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
bool AppWindow::removeScene(int index)
{
	this->scenes.erase(this->scenes.begin() + index);
	
	return true;
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
	this->window.create(sf::VideoMode(800, 600), "The Game"); // Temp name
	this->window.setFramerateLimit(60);
}


// Test to see if the window is opening
int main()
{
	AppWindow window;
	window.gameLoop();
	
	return 0;
}

