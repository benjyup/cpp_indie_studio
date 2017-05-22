#include <iostream>
#include "MapIndie.hpp"
#include "ObjectMap.hpp"
#include "IObject.hpp"
#include <irrlicht.h>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int	main()
{
  irr::video::E_DRIVER_TYPE driverType = driverType = irr::video::EDT_OPENGL;
  irr::IrrlichtDevice *device =
    irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(640, 640));

  irr::video::IVideoDriver* driver = device->getVideoDriver();
  irr::scene::ISceneManager* smgr = device->getSceneManager();
  irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
  
  Indie::MapIndie	myMap("./map01.txt", smgr, driver);
  irr::scene::IAnimatedMesh *mesh = smgr->getMesh("cube.obj");
  Indie::IObject *caseMapSol = new Indie::ObjectMap((int) Indie::TYPEOBJECT::UNDEFINED, mesh, 10, smgr,driver);

  caseMapSol->setPosition(-10,-10,-10);


  smgr->addCameraSceneNodeFPS();
  device->getCursorControl()->setVisible(false);

  // smgr->addCameraSceneNode(0, irr::core::vector3df(50,300,0), irr::core::vector3df(0, 5,0));
  //device->getCursorControl()->setVisible(true);
  int i =-10000000;
  while(device->run())
    {
      if (i % 6 == 0)
	caseMapSol->burn();
      else
	caseMapSol->changeType(Indie::TYPEOBJECT::UNDEFINED);
      driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

      smgr->drawAll();
      guienv->drawAll();

      driver->endScene();
      i++;
    }
  device->drop();
  return 0;
  //Q  IObject fire("fire", 1, 1);
  
  // myMap.addObject("fire", 1, 1);
  // my_map.moveObject(fire);
}
