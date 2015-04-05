#ifndef APPWINDOW_H_
#define APPWINDOW_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine/Scene.h"
#include "Logic/GameScene.h"
#include "Logic/MainMenuScene.h"
#include "Logic/ClientLobbyScene.h"
#include "Logic/ClientScoreboardScene.h"


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
		static AppWindow& getInstance();
		sf::View getCurrentView() const;
		sf::Vector2f getMousePositionRelativeToWindowAndView(const sf::View &view) const;
		void run();
		int	addScene(Scene * scene);
		void removeScene(int index);
	private:
		AppWindow();
		std::vector<Scene*> scene;
		bool isRunning = false;
		sf::Time m_elapsedTime, m_timePerFrame, m_timeSinceLastUpdate;
	};
}

#endif /* APPWINDOW_H_ */
