//
// Created by vincent on 07.5f/07.5f/17.
//

# include <map>
# include <iostream>
# include <irrlicht.h>
#include <vector>
#include "map.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define SQUARE_SIZE 15

using namespace irr;

static std::vector<int>        map =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1,
		1, 2, 1, 2, 1, 0, 0, 2, 0, 0, 0, 0, 1, 2, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 2, 1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 2, 1,
		1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

//static std::vector<int>        map =
//	{
//		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//		1, 8, 0, 2, 2, 0, 0, 3, 0, 0, 2, 2, 0, 0, 1,
//		1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1,
//		1, 2, 1, 4, 7, 0, 0, 2, 0, 0, 7, 4, 1, 2, 1,
//		1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
//		1, 0, 2, 2, 0, 0, 0, 5, 0, 0, 0, 2, 2, 0, 1,
//		1, 0, 1, 0, 1, 7, 1, 0, 1, 7, 1, 0, 1, 0, 1,
//		1, 2, 0, 6, 0, 6, 0, 1, 0, 5, 0, 4, 0, 2, 1,
//		1, 0, 1, 0, 1, 7, 1, 0, 1, 7, 1, 0, 1, 0, 1,
//		1, 0, 2, 2, 0, 0, 0, 3, 0, 0, 0, 2, 2, 0, 1,
//		1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
//		1, 2, 1, 3, 7, 0, 0, 2, 0, 0, 7, 3, 1, 2, 1,
//		1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1,
//		1, 0, 0, 2, 2, 0, 0, 4, 0, 0, 2, 2, 0, 0, 1,
//		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
//	};

int 		main()
{
  IrrlichtDevice *device =
	  createDevice( video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

  if (!device)
    return 1;
  device->setWindowCaption(L"BenjonaBenjo");
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();
  gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
  is::map(driver, smgr, map);

  while(device->run())
    {
      if (device->isWindowActive())
	{
	  driver->beginScene(true, true, video::SColor(255,200,200,200));
	  smgr->drawAll();
	  driver->endScene();
	}
      else
	device->yield();
    }

}