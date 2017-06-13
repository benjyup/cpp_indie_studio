//
// Created by peixot_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_FIRE_HPP
#define CPP_INDIE_STUDIO_FIRE_HPP

#include <iostream>
#include <map>
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

class Fire
{
 public:
  Fire(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, irr::core::vector3df Position,
       FireDirection Direction, float power);
  ~Fire();

  void						initMapDir();
  void						createBox(FireDirection Direction, irr::f32 power);
  void						createFire(irr::scene::ISceneManager* smgr, irr::core::vector3df Position);
  void						setPosition(irr::core::vector3df position);
  void						setScale(irr::core::vector3df scale);

 private:
  irr::scene::IParticleSystemSceneNode		*_ps;
  irr::scene::IParticleAffector			*_paf;
  irr::scene::IParticleEmitter			*_em;
  irr::video::ITexture				*_fireText;
  std::map<FireDirection, irr::core::vector3df>	_direction;
};

#endif //CPP_INDIE_STUDIO_FIRE_HPP
