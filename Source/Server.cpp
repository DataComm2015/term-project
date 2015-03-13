//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"
#include "Engine/ServerGameScene.h"

bool isRunning;
sf::Time m_elapsedTime, m_timePerFrame, m_timeSinceLastUpdate;
Scene *scene;

void run();


int main()
{
	scene = new ServerGameScene();
	run();
	delete scene;
	return 0;
}

void run()
{
	if (!isRunning)
	{
		isRunning = true;

		sf::Clock clock;
		sf::Event event;

		// LOOP
		while (isRunning)
		{
			// TIME UPDATES
			m_elapsedTime = clock.restart();
			m_timeSinceLastUpdate += m_elapsedTime;

			// TIME PER FRAME CONTROLLED LOOP
			while (m_timeSinceLastUpdate > m_timePerFrame)
			{
				m_timeSinceLastUpdate -= m_timePerFrame;

				scene->update(m_timePerFrame);
			}
		}

		isRunning = false;
	}
}
