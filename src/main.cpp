//
// Created by vincent on 05/05/17.
//

# include "GameEngine.hpp"
# include "GameState.hpp"
#include "MenuState.hpp"

int 		main(void) {
  try {

      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio", 1920, 1080);
      std::shared_ptr<is::IGameState> gameState = std::make_shared<is::MenuState>();

      // load the intro
      // game.ChangeState( CIntroState::Instance() );

      engine->ChangeState(gameState.get());

      // main loop
      while (engine->Running())
	{
	  engine->HandleEvents();
	  engine->Update();
	  engine->Draw();
	}
    } catch (const std::exception &e) {
      if (!std::string(e.what()).empty())
	std::cerr << "Error: " << e.what() << std::endl;
    }

  // cleanup the engine
  return 0;
}
