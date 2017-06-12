//
// Created by peixot_b on 12/06/17.
//

#include "Camera.hpp"
#include "map.hpp"

Camera::Camera(irr::scene::ISceneManager* smgr, CamMode cameraMode) : _smgr(smgr), _currMode(cameraMode)
{

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
