//
// Created by vincent on 05/05/17.
//

# include "GameEngine.hpp"
# include "GameState.hpp"

int 		main(void) {
  std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio");
  std::shared_ptr<is::IGameState> gameState = std::make_shared<is::GameState>();

  // load the intro
  // game.ChangeState( CIntroState::Instance() );

  engine->ChangeState(gameState);

  // main loop
  while (engine->Running())
  {
    engine->HandleEvents();
    engine->Update();
    engine->Draw();
  }

  // cleanup the engine
  return 0;
}