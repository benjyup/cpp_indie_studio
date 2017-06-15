//
// Created by peixot_b on 23/05/17.
//

#include <iostream>
#include "Fire.hpp"
#include "map.hpp"
#include <irrlicht.h>

Fire::Fire(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver,
	   irr::core::vector3df Position, FireDirection Direction, float power)
{
  initMapDir();
  std::cout << "power = " << power << std::endl;
  _fireText = driver->getTexture("./gfx/fire.bmp");
  _ps = smgr->addParticleSystemSceneNode(false);
  createBox(Direction, power);
  createFire(smgr, Position);
  _ps->setEmitter(0);
}


Fire::~Fire()
{
}

void Fire::startFire()
{
  _ps->setEmitter(_em);
}

void Fire::stopFire()
{
  _ps->setEmitter(0);
  _em->drop();
  _ps->remove();
}

void	Fire::initMapDir()
{
  std::map<FireDirection, irr::core::vector3df> m;
  m = {{FORWARD, irr::core::vector3df(0.00f, 0.00f, 0.015f)},
       {BACKWARD, irr::core::vector3df(0.00f, 0.00f, -0.015f)},
       {LEFT, irr::core::vector3df(-0.015f, 0.0f, 0.0f)},
       {RIGHT, irr::core::vector3df(0.015f, 0.00f, 0.0f)},
       {TOP, irr::core::vector3df(0.00f, 0.015f, 0.0f)},
       {DOWN, irr::core::vector3df(0.00f, -0.015f, 0.0f)}};
  _direction = m;
}

void	Fire::createBox(FireDirection Direction, irr::f32 power)
{
  irr::core::vector3df	newPower(power * 1.5, power * 1.5, power * 1.5);

  for (auto it = _direction.begin(); it != _direction.end(); it++)
    {
      if (it->first == Direction)
	{
	  _em = _ps->createBoxEmitter(
		  irr::core::aabbox3d<irr::f32>(-7, 0, -7, 7, 1, 7),
		  irr::core::vector3df(it->second * newPower),
		  80, 100,
		  irr::video::SColor(0, 255, 255, 0),
		  irr::video::SColor(0, 255, 255, 0),
		  200, 800, 0,
		  irr::core::dimension2df(10.f, 10.f),
		  irr::core::dimension2df(20.f, 20.f));
	  break;
	}
    }
}

void	Fire::createFire(irr::scene::ISceneManager* smgr, irr::core::vector3df Position)
{
  _ps->setEmitter(_em);
  _paf = _ps->createFadeOutParticleAffector();
  _ps->addAffector(_paf);
  _paf->drop();
  _ps->setPosition(Position);
  _ps->setScale(irr::core::vector3df(0.001 * (SCALE - 1), 0.001 * (SCALE - 1), 0.001 * (SCALE - 1)));
  _ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  _ps->setMaterialTexture(0, _fireText);
  _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  std::cout << "debut createFire" << std::endl;
}

void	Fire::setPosition(irr::core::vector3df position)
{
  _ps->setPosition(position);
}

void	Fire::setScale(irr::core::vector3df scale)
{
  _ps->setScale(scale);
}

void Fire::draw()
{
  _ps->render();
}
