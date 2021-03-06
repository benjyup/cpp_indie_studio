//
// Created by peixot_b on 24/05/17.
//

#ifndef CPP_INDIE_STUDIO_PLANETSYSTEM_HPP
#define CPP_INDIE_STUDIO_PLANETSYSTEM_HPP

#include <iostream>
#include <irrlicht.h>

namespace is
{
  class PlanetSystem
  {
   public:
    PlanetSystem(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, const irr::io::path &filename,
		 irr::f32 radius, irr::f32 speed, irr::core::vector3df position);

    ~PlanetSystem();

    void draw();

   private:
    irr::scene::ISceneNode *_node;
  };
}

#endif //CPP_INDIE_STUDIO_PLANETSYSTEM_HPP
