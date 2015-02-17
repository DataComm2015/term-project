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
*		compile with: 	-std=c++11
*		libraries:		-lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
******************************************************************************/
bool AppWindow::gameLoop()
{
	// Display the window
	this->window_.clear();
    this->window_.display();
	
	while(this->window_.isOpen())
	{
			for(std::vector<Scene*>::iterator it = this->scenes_.begin();
				it != this->scenes_.end();
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
	this->scenes_.push_back(scene);
	
	// return id of the scene added. used for removeScene. Either return
	// id after adding or overload == operator for the scene.
	return (this->scenes_.size() - 1);
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
	// Just realized that this will only work for the first removeScene call
	// as the index will change for the remaining elements. Might change the 
	// collection to Map instead of a vector
	this->scenes_.erase(this->scenes_.begin() + index);
	
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
	this->window_.create(sf::VideoMode(800, 600), "The Game"); // Temp name
	this->window_.setFramerateLimit(60);
}


// Test to see if the window is opening
int main()
{
	AppWindow window;
	window.gameLoop();
	
	return 0;
}

