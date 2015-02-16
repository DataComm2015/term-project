#ifndef APPWINDOW_H_
#define APPWINDOW_H_

#include <vector>
#include "Scene.cpp"

/* 
*	AppWindow is responsible for running the game loop. The game loop processes 
*	turns for all of the scenes. Each scene is loaded into the app window on 
*	creation and will not have a loop of its own for the sake of synchronisation.
*   
*/
class AppWindow
{
	
	public:
	
	bool	gameLoop();
	int		addScene(Scene* scene);
	bool	removeScene(int index);
	
	private:
		std::vector<Scene*> scenes;
};

#endif /* APPWINDOW_H_ */
