//
// Created by peixot_b on 12/06/17.
//

#include <thread>
#include <iostream>
#include "Camera.hpp"
#include "map.hpp"
#include "IGameState.hpp"

Camera::Camera(irr::scene::ISceneManager* smgr, CamMode cameraMode, is::GameEngine *engine)
	: _smgr(smgr), _currMode(cameraMode), _engine(engine)
{
  _timer = _engine->getDevice()->getTimer();
}

Camera::~Camera()
{

}

void			Camera::setMenuMode()
{
  irr::scene::ISceneNodeAnimator* anim = 0;
  anim = _smgr->createFlyCircleAnimator(irr::core::vector3df(0,200,0), 400.0f, 0.0009f);
  _smgr->addCameraSceneNode(0, irr::core::vector3df(BLOCK / 2 * SCALE, 2000, BLOCK / 2 * 100),
			   irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2,
						0.0f,
						((0.5 + (BLOCK - 1)) * SCALE)) / 2)->addAnimator(anim);
  anim->drop();
}

void			Camera::setInGameMode()
{
  _smgr->addCameraSceneNode(0, irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2, 220, -80),
			    irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2,
						 0.0f,
						 ((0.5 + (BLOCK - 1)) * SCALE) / 2));
}

void			Camera::setSplashScreen()
{
  irr::scene::ICameraSceneNode *camera;
  irr::scene::ISceneNodeAnimator *anim = 0;

  camera = _smgr->addCameraSceneNode(0,
				     irr::core::vector3df(BLOCK / 2 * SCALE, 2000, BLOCK / 2 * 100),
				     irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2,
							  0.0,
							  ((0.5 + (BLOCK)) * SCALE) / 2));
  anim = _smgr->createFlyStraightAnimator(irr::core::vector3df(0, 20, -2750),
					  irr::core::vector3df(0, 3 * SCALE, 100),
					  5000, false, false);
  camera->addAnimator(anim);
  while (_engine->Running())
    {
      std::cout << _timer->getTime() << std::endl;
      _engine->HandleEvents();
      _engine->Update();
      _engine->Draw();
    }

//  anim = _smgr->createFlyStraightAnimator(irr::core::vector3df(0, 3 * SCALE, 100),
//					  irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2,
//							       1000,
//							       ((0.5 + (BLOCK)) * SCALE) / 2),
//					  5000, false, false);
//  camera->addAnimator(anim);
  anim->drop();
}

scene::ISceneManager	*Camera::get_smgr() const
{
  return _smgr;
}

CamMode			Camera::get_currMode() const
{
  return _currMode;
}

void			Camera::set_smgr(scene::ISceneManager *_smgr)
{
  Camera::_smgr = _smgr;
}

void			Camera::set_currMode(CamMode _currMode)
{
  Camera::_currMode = _currMode;
}
