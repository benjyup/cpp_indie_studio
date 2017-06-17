//
// Created by vincent on 05/05/17.
//

# include "GameEngine.hpp"
# include "GameState.hpp"
# include "MenuState.hpp"
# include "IntroState.hpp" 

int 		main(void) {
  try {

      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio",
										1900, 1000, 0, false);
      engine->PushState(new is::MenuState);

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
