#include "GameRound.h"

/******************************************************************************

Game Round
  start lobby in a user-input responsive loop
    client -> select potential job class
    client -> select potential deity class
    server -> if all players ready
              randomly assign players to vessels
              if players left over, randomly assign players to deities
              send start loading screen signal, end loop
    client -> if received start loading screen signal, end loop
              else server stops, terminate and start

  // server ready
  loading screen
    server -> load scenario
              send scenario
    client -> load scenario from server info
    server -> check player connections
              if player timed out, kick player
                if player was a vessel, move random deity to vessel position

  server -> game field loop
            if time not expired yet

            else
              send game over signal to client
              tally up scores
              clean up memory

  client -> game field loop
            if not game over yet

            else
              clean up memory


******************************************************************************/
