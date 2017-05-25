#include <iostream>
#include <string>
//#include "MapIndie.hpp"

#include "Fire.hpp"
#include "Bombs.hpp"
#include "ParseMap.hpp"
#include "map.hpp"
//#include "PlanetSystem.hpp"

#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


int	main()
{
  irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;
  irr::IrrlichtDevice *device = irr::createDevice(driverType,
						  irr::core::dimension2d<irr::u32>(1920, 1080),
						  16, false, false, false, 0);

  irr::video::IVideoDriver* driver = device->getVideoDriver();
  irr::scene::ISceneManager* smgr = device->getSceneManager();
  irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

  //std::cout <<  << std::endl;

  irr::core::string<char>	a = device->getFileSystem()->getWorkingDirectory();
  std::cout << " coucou " << std::endl;
  std::cout << a.c_str() << std::endl;
  is::ParseMap toto("map02.txt");
  is::map	myMap(driver, smgr, toto.getVector());
  irr::scene::IAnimatedMesh *mesh = smgr->getMesh("./gfx/cube.obj");
  //Indie::IObject *caseMapSol = new Indie::ObjectMap((int) Indie::TYPEOBJECT::UNDEFINED, mesh, 10, smgr,driver);
  //caseMapSol->setPosition(-10,-10,-10);




  // SOLEIL GRAVITANT
  //  PlanetSystem	Planet(smgr, driver, "./gfx/particlered.bmp", 800.0f, 0.01f);


  smgr->addCameraSceneNodeFPS();
  device->getCursorControl()->setVisible(false);


  // Fire	fire(smgr, driver, irr::core::vector3df(-5, 0, 5), TOP);
  // Fire	fire2(smgr, driver, irr::core::vector3df(-5, 0, 145), TOP);
  //  Fire	fire3(smgr, driver, irr::core::vector3df(135, 0, 5), TOP);
  //  Fire	fire4(smgr, driver, irr::core::vector3df(135, 0, 145), TOP);
  is::Bombs binta(&myMap, driver,smgr);
  irr::video::ITexture*  	space = driver->getTexture("./gfx/space3.jpg");

  int lastFPS = -1;
  smgr->addSkyDomeSceneNode(space,16,16,1.0f,1.0f)->setRotation(irr::core::vector3df(0, 0, -180));
  smgr->addSkyDomeSceneNode(space,16,16,1.0f,1.0f);

  int i = -10000;
  is::Vector3d pos(5,5,0);
  //  Fire	fire4(smgr, driver, irr::core::vector3df(135, 0, 145), TOP);
  binta.putBomb(pos, 1);
  while(device->run())
    {
      //      if (i == -10000)
      //	Fire	fire4(smgr, driver, irr::core::vector3df(135, 0, 145), TOP);
      //	binta.putBomb(pos, 1);
      if (device->isWindowActive())
	{
	  driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
	  smgr->drawAll();
	  driver->endScene();
	  driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

	  guienv->drawAll();

	  int fps = driver->getFPS();

	  if (lastFPS != fps)
	    {
	      irr::core::stringw str = L"BENJO NA BENJO GAME[";
	      str += driver->getName();
	      str += "] FPS:";
	      str += fps;

	      device->setWindowCaption(str.c_str());
	      lastFPS = fps;
	    }
	}
      else
	device->yield();
      i++;
    }
}
