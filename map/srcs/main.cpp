//
// Created by vincent on 07.5f/07.5f/17.
//

# include <map>
# include <iostream>
# include <irrlicht.h>
#include "irrKlang.h"
#include  <vector>
#include "Game.hpp"
#include "Sound.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define SQUARE_SIZE 15

using namespace irr;

int 		main()
{
  Sound		music;

  // Exemple d'utilisation de la music
  music.setGameMusic();
  //music.setMenuMusic();
  //music.setGameMusicWin();
  try
    {
      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio", 1024, 768, 0, false);

      engine->ChangeState(new is::Game);
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
