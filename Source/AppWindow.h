#ifndef APPWINDOW_H_
#define APPWINDOW_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine/Scene.h"
#include "Engine/EG_Scene.h"


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
			AppWindow() : sf::RenderWindow(sf::VideoMode(800, 600), "The Game") 
			{
				Scene *s = new Scene;
				EG_Scene *s2 = new EG_Scene;
				scene.emplace_back(s);
				scene.emplace_back(s2);
				timePerFrame = sf::milliseconds(60);
			};
		
		private:
			std::vector<Scene*> scene;
			bool isRunning = false;
			sf::Time nextUpdate, timePerFrame;
	};

}

int main();

#endif /* APPWINDOW_H_ */
