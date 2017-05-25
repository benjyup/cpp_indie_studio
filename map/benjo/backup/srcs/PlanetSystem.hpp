//
// Created by peixot_b on 24/05/17.
//

#ifndef CPP_INDIE_STUDIO_PLANETSYSTEM_HPP
#define CPP_INDIE_STUDIO_PLANETSYSTEM_HPP

#include <iostream>
#include <irrlicht.h>

class PlanetSystem
{
 public:
  PlanetSystem(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, const irr::io::path &filename,
	       irr::f32 radius, irr::f32 speed);
  ~PlanetSystem();

 private:
};


#endif //CPP_INDIE_STUDIO_PLANETSYSTEM_HPP
