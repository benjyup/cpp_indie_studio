//
// Created by peixot_b on 23/05/17.
//

#include <iostream>
#include "Fire.hpp"
#include "map.hpp"
#include <irrlicht.h>
#include <PowerUpManager.hpp>

const std::map<is::FireDirection, std::function<void(irr::core::vector3di &pos)>> is::Fire::_DIRECTIONS_ACTION = {
	{is::FORWARD,  [](irr::core::vector3di &pos) { pos.X += 1; }},
	{is::BACKWARD, [](irr::core::vector3di &pos) { pos.X -= 1; }},
	{is::RIGHT,    [](irr::core::vector3di &pos) { pos.Y += 1; }},
	{is::LEFT,     [](irr::core::vector3di &pos) { pos.Y -= 1; }}
};

is::Fire::Fire(is:: map &map, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver,
	   irr::core::vector3df Position, irr::core::vector3df posMap, FireDirection Direction, float power, is::PowerUpManager *pm) :
	_power(power),
	_map(map),
	_pos({posMap.X, posMap.Y, posMap.Z}),
	_dir(Direction),
	_isBreakable(false),
    _pm(pm)
{
  initMapDir();
  std::cout << "power = " << power << std::endl;
  _fireText = driver->getTexture("./gfx/fire.bmp");
  _ps = smgr->addParticleSystemSceneNode(false);
  createBox(Direction, power);
  createFire(smgr, Position);
  _ps->setEmitter(0);
}


is::Fire::~Fire()
{
}

void	is::Fire::startFire()
{
  irr::core::vector3di  pos(this->_pos);

  _ps->setEmitter(_em);
  std::cerr << "START FIRE" << std::endl;
  for (float i = 0.0f ; i <= _power ; i += 1)
    {
      std::cout << "START FIRE pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      if (this->_map.getLocalType({pos.X, pos.Y, pos.Z}) == BREAK)
      {
          this->_isBreakable = true;
          _pow.X = pos.X;
          _pow.Y = pos.Y;
      }
        if (this->_map.getLocalType({pos.X, pos.Y, pos.Z}) == POWERUP)
        {
            std::cerr << "COLLISION FIRE POWERUP" << std::endl;
            _pm->getPowerUp({pos.X, pos.Y, pos.Z});
        }
      this->_map.addObject(is::Type::FIRE, {pos.X, pos.Y, pos.Z});
      _DIRECTIONS_ACTION.at(this->_dir)(pos);
    }
  std::cerr << "START FIRE" << std::endl;
}

void	is::Fire::stopFire(is::PowerUpManager &pm)
{
  _ps->setEmitter(0);
  _em->drop();
  _ps->remove();
  std::cerr << "DELETE FIRE" << std::endl;
  irr::core::vector3di  pos(this->_pos);
  for (float i = 0.0f ; i <= _power ; i += 1)
    {
      std::cout << "DELETE FIRE pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      this->_map.delObject({pos.X, pos.Y, pos.Z});
      _DIRECTIONS_ACTION.at(this->_dir)(pos);
    }

  if (this->_isBreakable)
    pm.newPow(irr::core::vector3df(_pow.X, _pow.Y, 0));

  std::cerr << "DELETE FIRE" << std::endl;
}

void	is::Fire::initMapDir()
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

void	is::Fire::createBox(FireDirection Direction, irr::f32 power)
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

void	is::Fire::createFire(irr::scene::ISceneManager* smgr, irr::core::vector3df Position)
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

void	is::Fire::setPosition(irr::core::vector3df position)
{
  _ps->setPosition(position);
}

void	is::Fire::setScale(irr::core::vector3df scale)
{
  _ps->setScale(scale);
}

void	is::Fire::draw()
{
  _ps->render();
}

void is::Fire::set_pm(is::PowerUpManager *pm) {
    _pm = pm;
}
