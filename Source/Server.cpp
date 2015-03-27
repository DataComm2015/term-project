//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"

#include "Logic/ServerCommand.h"
#include "Logic/Entities/ServerCommandEntity.h"
#include "Logic/ServerGameScene.h"
#include "Network/NetworkController.h"
#include "Network/NetworkEntityMultiplexer.h"

#include <string.h>
#include <stdio.h>

// namespace
using Networking::NetworkEntityMultiplexer;
using Networking::NetworkController;
using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;
using Networking::Server;

// globals
void run(Scene *scene);

//////////
// main //
//////////

int main( int argc, char ** argv )
{
    Scene *scene;

    printf("USAGE: %s [LOCAL_PORT]\n",argv[0]);
    fflush(stdout);

    scene = new ServerGameScene();

    ServerCommand server(scene);
    server.startServer(atoi(argv[1]));

    run(scene);

    delete scene;
    return 0;
}

/**
 * the game loop.
 */
void run(Scene *scene)
{
    bool isRunning;
    sf::Time m_elapsedTime;
    sf::Time m_timePerFrame;
    sf::Time m_timeSinceLastUpdate;
    sf::Time m_sleepTime;

    m_sleepTime = sf::seconds(1.0/75);
    m_timePerFrame = sf::seconds(1.0/60);

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

                sf::sleep(m_sleepTime);
            }
        }

        
        isRunning = false;
    }
}
