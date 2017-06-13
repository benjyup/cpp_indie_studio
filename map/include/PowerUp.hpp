//
// Created by Jean-Adrien on 13/06/17.
//

#ifndef MAP_POWERUP_HPP
#define MAP_POWERUP_HPP

#include "Options.hpp"
#include <string>
#include <dirent.h>

namespace is
{
    class PowerUp
    {
    public:
        PowerUp(irr::scene::IAnimatedMesh *,
                 irr::video::ITexture *,
                 irr::scene::ISceneManager *,
                 irr::core::vector3df const &);
        ~PowerUp() {};
    private:
        irr::scene::IAnimatedMeshSceneNode  *_mesh;
        irr::video::ITexture                *_text;
        irr::scene::ISceneManager           *_smgr;
        irr::core::vector3df                _pos;
    };
}

#endif //MAP_POWERUP_HPP
