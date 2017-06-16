//
// Created by peixot_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_FIRE_HPP
#define CPP_INDIE_STUDIO_FIRE_HPP

#include <iostream>
#include <map>
#include "map.hpp"
#include <irrlicht.h>

enum	FireDirection
{
  FORWARD = 0,
  BACKWARD,
  LEFT,
  RIGHT,
  TOP,
  DOWN
};

namespace is
{
  class map;
}

class Fire
{
 public:
  Fire(is::map &map, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, irr::core::vector3df Position, irr::core::vector3df posMap,
       FireDirection Direction, float power);
  ~Fire();

  void						initMapDir();
  void						createBox(FireDirection Direction, irr::f32 power);
  void						createFire(irr::scene::ISceneManager* smgr, irr::core::vector3df Position);
  void						setPosition(irr::core::vector3df position);
  void						setScale(irr::core::vector3df scale);

  void						startFire();
  void 						stopFire();
  void 						draw();
 private:
  static const std::map<FireDirection, std::function<void(irr::core::vector3di &pos)>>	_DIRECTIONS_ACTION;
  irr::scene::IParticleSystemSceneNode		*_ps;


  irr::scene::IParticleAffector			*_paf;
  irr::scene::IParticleEmitter			*_em;
  irr::video::ITexture				*_fireText;
  std::map<FireDirection, irr::core::vector3df>	_direction;
  float 					_power;
  is::map					&_map;
  irr::core::vector3di				_pos;
  FireDirection 				_dir;

};

#endif //CPP_INDIE_STUDIO_FIRE_HPP
