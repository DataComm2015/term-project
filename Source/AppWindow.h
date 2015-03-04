#ifndef APPWINDOW_H_
#define APPWINDOW_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine/Scene.h"
#include "Engine/EG_Scene.h"
#include "Logic/GameScene.h"


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
			void run();
			int	addScene(Scene * scene);
			void removeScene(int index);
			static AppWindow * getInstance();
		private:
			AppWindow();
			static AppWindow * app;
			std::vector<Scene*> scene;
			bool isRunning = false;
			sf::Time nextUpdate, timePerFrame;
	};

}

int main();

#endif /* APPWINDOW_H_ */
