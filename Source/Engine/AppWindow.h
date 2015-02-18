#ifndef APPWINDOW_H_
#define APPWINDOW_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "Scene.cpp"

namespace Marx
{
	/* 
	*	AppWindow is responsible for running the game loop. The game loop processes 
	*	turns for all of the scenes. Each scene is loaded into the app window on 
	*	creation and will not have a loop of its own for the sake of synchronisation.
	*   
	*/
	class AppWindow
	{
		public:
		int		initWindow();
		bool	gameLoop();
		int		addScene(Scene* scene);
		bool	removeScene(int index);
		AppWindow();
		
		private:
			sf::RenderWindow window_;
			std::vector<Scene*> scenes_;
	};
} /* namespace Marx */

#endif /* APPWINDOW_H_ */
