/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Lobby.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 16, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- NOTES:
--        This file defines the Lobby class members
--
----------------------------------------------------------------------------------------------------------------------*/

#ifndef LOBBY_H_
#define LOBBY_H_

#include <vector>

namespace Marx
{
    /* 
    *    Class that handles the lobby for the game
    */
    class Lobby
    {
        public:
            bool join(void* player);
            bool leave(void* player);
            bool joinable();
            
            // Getters and setters
            std::vector<void*> getPlayerQueue();
            std::vector<void*> getSpectatorQueue();
            bool getJoinBlock();
            void setJoinBlock(bool state);
            
        private:

            std::vector<void*> playerQueue_;
            std::vector<void*> spectatorQueue_;

            int playerLimit_;    // Network or logic team to set
            int spectatorLimit_;    // Network or logic team to set

            bool joinBlock_;
    };
} /* namespace Marx */

#endif /* LOBBY_H_ */
