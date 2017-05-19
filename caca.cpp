//
// Created by vincent on 05/05/17.
//

# include <map>
# include <iostream>
# include <irrlicht.h>
#include <vector>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define SQUARE_SIZE 10

using namespace irr;

int 		main()
{
  IrrlichtDevice *device =
	  createDevice( video::EDT_SOFTWARE, core::dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

  if (!device)
    return 1;
  device->setWindowCaption(L"BenjonaBenjo");
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();
  gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
  std::vector<std::vector<scene::IAnimatedMeshSceneNode *>>			map;
  video::ITexture 								*text[3];

  text[0] = driver->getTexture("./gfx/groundGrass.png");
  text[1] = driver->getTexture("./gfx/wallBrick.png");
  text[2] = driver->getTexture("./gfx/wallStone.png");
  scene::IAnimatedMesh* mesh = smgr->getMesh("./gfx/wallBrick.obj");
  for (int i = 0; i < SQUARE_SIZE; i++)
    {
      map.push_back(std::vector<scene::IAnimatedMeshSceneNode *>());
      for (int j = 0; j < SQUARE_SIZE; j++)
	{
	  map[i].push_back(smgr->addAnimatedMeshSceneNode(mesh));
	  map[i][j]->setMaterialFlag(video::EMF_LIGHTING, false);
	  map[i][j]->setMD2Animation(scene::EMAT_STAND);
	  map[i][j]->setMaterialTexture(0, text[(i + j) % 3]);
	  map[i][j]->setScale(core::vector3df(10, 10, 10));
	  map[i][j]->setPosition(core::vector3df(i * 10, j * 10, ));
	  std::cout << "here" << i << std::endl;
	}
    }

  scene::IAnimatedMesh* mesh5 = smgr->getMesh("./gfx/wallStone.obj");
  smgr->getMeshManipulator()->makePlanarTextureMapping(mesh5->getMesh(0), 0.004f);
  scene::ISceneNode* node5 = 0;

  node5 = smgr->addAnimatedMeshSceneNode(mesh5);
  node5->setMaterialTexture(0, driver->getTexture("./gfx/water.jpg"));
  node5->getMaterial(0).SpecularColor.set(0,0,0,0);


  mesh5 = smgr->addHillPlaneMesh( "myHill",
				  core::dimension2d<f32>(20,20),
				  core::dimension2d<u32>(40,40), 0, 0,
				  core::dimension2d<f32>(0,0),
				  core::dimension2d<f32>(10,10));

  node5 = smgr->addWaterSurfaceSceneNode(mesh5->getMesh(0), 3.0f, 300.0f, 30.0f);
  node5->setPosition(core::vector3df(0,-30,0));
  node5->setMaterialTexture(0, driver->getTexture("./gfx/water.jpg"));
  node5->setMaterialTexture(1, driver->getTexture("./gfx/water.jpg"));
  node5->setMaterialType(video::EMT_REFLECTION_2_LAYER);
  smgr->addCameraSceneNode(0, core::vector3df(0,150,0), core::vector3df(0,5,0));
  //smgr->addCameraSceneNodeFPS();
  //device->getCursorControl()->setVisible(false);

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