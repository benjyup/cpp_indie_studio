//
// Created by vincent on 07.5f/07.5f/17.
//

# include <map>
# include <iostream>
# include <irrlicht.h>
#include "irrKlang.h"
#include  <vector>
#include "Game.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define SQUARE_SIZE 15

using namespace irr;

int 		main()
{
  irrklang::ISoundEngine* engine2 = irrklang::createIrrKlangDevice();

  if (!engine2)
    return 0;
  engine2->play2D("./gfx/music1.ogg", true);
  try
    {
      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio", 1024, 768, 0, false);
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
  engine2->drop();
  return 0;
}
