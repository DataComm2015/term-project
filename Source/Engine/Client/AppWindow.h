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
	class AppWindow : public sf::RenderWindow
	{
		public:
		int		initWindow();
		void	run();
		void	addScene(Scene* scene);
		void	removeScene(int index);
		AppWindow();
		
		private:
			std::vector<Scene*> scene;	// Map so that named scenes can be removed.
			bool isRunning = false;
			sf::Time elapsedTime, timePerFrame, timeSinceLastUpdate;
	};

}

#endif /* APPWINDOW_H_ */
