//
// Created by vincent on 05/05/17.
//

# include <irrlicht.h>

/*
 * int 		main(void) {
  is::GameEngine game("Indie Studio");
  is::IGameState *gameState = new is::GameState;

  // load the intro
  // game.ChangeState( CIntroState::Instance() );

  game.ChangeState(gameState);

  // main loop
  while (game.Running()) {
     game.HandleEvents();
    game.Update();
    game.Draw();
  }

  // cleanup the engine
  return 0;
}
 */

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

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

  scene::IAnimatedMesh* mesh = smgr->getMesh("./gfx/wallBrick.obj");
  scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
  if (node)
    {
      node->setMaterialFlag(video::EMF_LIGHTING, false);
      node->setMD2Animation(scene::EMAT_STAND);
      node->setMaterialTexture( 0, driver->getTexture("./gfx/groundGrass.png") );
      node->setScale(core::vector3df(10,10,10));
      node->setPosition(core::vector3df(0,0,0));
    }
  scene::IAnimatedMesh* mesh2 = smgr->getMesh("./gfx/wallBrick.obj");
  scene::IAnimatedMeshSceneNode* node2 = smgr->addAnimatedMeshSceneNode( mesh2 );
  if (node2)
    {
      node2->setMaterialFlag(video::EMF_LIGHTING, false);
      node2->setMD2Animation(scene::EMAT_STAND);
      node2->setMaterialTexture( 0, driver->getTexture("./gfx/groundGrass.png") );
      node2->setScale(core::vector3df(10,10,10));
      node2->setPosition(core::vector3df(0,0,10));
    }
  scene::IAnimatedMesh* mesh3 = smgr->getMesh("./gfx/wallBrick.obj");
  scene::IAnimatedMeshSceneNode* node3 = smgr->addAnimatedMeshSceneNode( mesh3 );
  if (node3)
    {
      node3->setMaterialFlag(video::EMF_LIGHTING, false);
      node3->setMD2Animation(scene::EMAT_STAND);
      node3->setMaterialTexture( 0, driver->getTexture("./gfx/groundGrass.png") );
      node3->setScale(core::vector3df(10,10,10));
      node3->setPosition(core::vector3df(10,0,0));
    }
  scene::IAnimatedMesh* mesh4 = smgr->getMesh("./gfx/wallBrick.obj");
  scene::IAnimatedMeshSceneNode* node4 = smgr->addAnimatedMeshSceneNode( mesh4 );
  if (node4)
    {
      node4->setMaterialFlag(video::EMF_LIGHTING, false);
      node4->setMD2Animation(scene::EMAT_STAND);
      node4->setMaterialTexture( 0, driver->getTexture("./gfx/groundGrass.png") );
      node4->setScale(core::vector3df(10,10,10));
      node4->setPosition(core::vector3df(10,0,10));
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


  int lastFPS = -1;

  while(device->run())
    {
      if (device->isWindowActive())
	{
	  driver->beginScene(true, true, video::SColor(255,200,200,200));
	  smgr->drawAll();
	  driver->endScene();
	  driver->beginScene(true, true, video::SColor(255,100,101,140));

	  guienv->drawAll();

	  int fps = driver->getFPS();

	  if (lastFPS != fps)
	    {
	      core::stringw str = L"Irrlicht Engine - Quake 3 Map example [";
	      str += driver->getName();
	      str += "] FPS:";
	      str += fps;

	      device->setWindowCaption(str.c_str());
	      lastFPS = fps;
	    }
	}
      else
	device->yield();
    }

}