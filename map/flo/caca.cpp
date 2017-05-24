//
// Created by vincent on 07.5f/07.5f/17.
//

# include <map>
# include <iostream>
# include <irrlicht.h>
#include  <vector>
#include "Game.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define SQUARE_SIZE 15

using namespace irr;

int 		main()
{
  try
    {
      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio", 1024, 768);
      std::shared_ptr<is::IGameState> gameState = std::make_shared<is::Game>();

      engine->ChangeState(gameState.get());
      engine->getDevice()->setResizable(true);

      while (engine->Running())
	{
	  engine->HandleEvents();
	  engine->Update();
	  engine->Draw();
	}
    }
  catch (const std::exception &e) {
    if (!std::string(e.what()).empty())
      std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
