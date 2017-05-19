//
// Created by vincent on 05/05/17.
//

# include "GameEngine.hpp"
# include "GameState.hpp"

int 		main(void) {
  is::GameEngine game("Indie Studio");
  is::IGameState *gameState = new is::GameState;

  // load the intro
  // game.ChangeState( CIntroState::Instance() );

  game.ChangeState(gameState);

  // main loop
  while (game.Running()) {
     game.HandleEvents();
    game.Update();
    game.Draw();
  }

  // cleanup the engine
  return 0;
}