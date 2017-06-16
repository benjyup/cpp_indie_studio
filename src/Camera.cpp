//
// Created by peixot_b on 12/06/17.
//

#include <thread>
#include <iostream>
#include "Camera.hpp"
#include "map.hpp"
#include "IGameState.hpp"
#include "MenuState.hpp"

is::Camera::Camera(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver *driver,
	       CamMode cameraMode, is::GameEngine *engine)
	: _smgr(smgr), _driver(driver), _currMode(cameraMode), _engine(engine), _anim(0),
	  _anim1Time(10000), _anim2Time(5000), _anim3Time(5000), _anim4Time(5000)
{
  _timer = _engine->getDevice()->getTimer();
}

is::Camera::~Camera()
{

}

void			is::Camera::setMenuMode()
{
  irr::scene::ISceneNodeAnimator* anim = 0;
  anim = _smgr->createFlyCircleAnimator(irr::core::vector3df(0,200,0), 400.0f, 0.0003f);
  _smgr->addCameraSceneNode(0, irr::core::vector3df(BLOCK / 2 * SCALE, 2000, BLOCK / 2 * 100),
			   irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2,
						0.0f,
						((0.5 + (BLOCK - 1)) * SCALE)) / 2)->addAnimator(anim);
  anim->drop();
}

void			is::Camera::setInGameMode()
{
  _smgr->addCameraSceneNode(0, irr::core::vector3df((((0.5 + (BLOCK - 2)) * SCALE) / 2) - 2, 150, 30),
			    irr::core::vector3df((((0.5 + (BLOCK - 2)) * SCALE) / 2) - 2,
						 0,
						 (((0.5 + (BLOCK - 1)) * SCALE) / 2)));
}

void			is::Camera::setAnimation1()
{
  _anim = _smgr->createFlyStraightAnimator(irr::core::vector3df(0, 3 * SCALE, -2750),
					  irr::core::vector3df(0, 3 * SCALE, 100),
					  _anim1Time, false, false);
  _camera->addAnimator(_anim);
}

void			is::Camera::setAnimation2()
{
  _node->setVisible(0);
  _anim = _smgr->createFlyStraightAnimator(irr::core::vector3df(0, 3 * SCALE, 100),
					   irr::core::vector3df(((0.4 + (BLOCK - 2)) * SCALE),
								1000,
								((0.4 + (BLOCK)) * SCALE)),
					   _anim2Time, false, false);
  _camera->addAnimator(_anim);
}

void			is::Camera::setAnimation3()
{
  _anim = _smgr->createFlyStraightAnimator(irr::core::vector3df(((0.4 + (BLOCK - 2)) * SCALE),
								1000,
								((0.4 + (BLOCK)) * SCALE)),
					   irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE),
								100,
								((0.5 + (BLOCK)) * SCALE)),
					   _anim3Time, false, false);
  _camera->addAnimator(_anim);
}

void			is::Camera::setTextMenu()
{
  _mesh = _smgr->getMesh("./gfx/bomberman3D.obj");
  _node = _smgr->addAnimatedMeshSceneNode(_mesh);
  if (_node)
    {
      _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _node->setMD2Animation(scene::EMAT_STAND);
      _node->setScale({10.0f, 10.0f, 10.0f});
      _node->setRotation({0, 180, 0});
      _node->setMaterialTexture( 0, _driver->getTexture("./gfx/fire.jpg"));
      _node->setPosition(irr::core::vector3df(BLOCK / 2 * SCALE, 2000, BLOCK / 2 * 100));
    }
  _node->setVisible(1);
}

void			is::Camera::draw()
{
  _camera->render();
  _node->render();
}

void 			is::Camera::setTextIntro()
{
  _mesh = _smgr->getMesh("./gfx/indiestudio2.obj");
  _node = _smgr->addAnimatedMeshSceneNode(_mesh);
  if (_node)
    {
      _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _node->setMD2Animation(scene::EMAT_STAND);
      _node->setScale({10.0f, 10.0f, 10.0f});
      _node->setRotation({0, 180, 0});
      _node->setMaterialTexture( 0, _driver->getTexture("./gfx/fire.jpg"));
      _node->setPosition({-14, 3 * SCALE - 5, -1600});
    }
}

void			is::Camera::setSplashScreen()
{
  _camera = _smgr->addCameraSceneNode(0,
				     irr::core::vector3df(BLOCK / 2 * SCALE, 2000, BLOCK / 2 * 100),
				     irr::core::vector3df(((0.5 + (BLOCK - 2)) * SCALE) / 2,
							  0.0,
							  ((0.5 + (BLOCK)) * SCALE) / 2));
  setTextIntro();
  setAnimation1();
  while (_engine->Running())
    {
      if (_timer->getTime() >= _anim1Time - 30 && _timer->getTime() <= (_anim1Time))
	setAnimation2();
      if (_timer->getTime() >= (_anim1Time + _anim2Time - 30) && _timer->getTime() <= (_anim1Time + _anim2Time))
	setAnimation3();
      _engine->HandleEvents();
      _engine->Update();
      _engine->Draw();
      if (_timer->getTime() >= (_anim1Time + _anim2Time + _anim3Time) - 30)
	{
	  //_smgr->clear();
    _engine->ChangeState(new is::MenuState);
	  break;
	}
    }
  _anim->drop();
}

scene::ISceneManager	*is::Camera::get_smgr() const
{
  return _smgr;
}

is::CamMode			is::Camera::get_currMode() const
{
  return _currMode;
}

void			is::Camera::set_smgr(scene::ISceneManager *_smgr)
{
  Camera::_smgr = _smgr;
}

void			is::Camera::set_currMode(CamMode _currMode)
{
  Camera::_currMode = _currMode;
}
