//
// Created by Jean-Adrien on 13/06/17.
//

#ifndef MAP_POWERUP_HPP
#define MAP_POWERUP_HPP

#include <string>
#include <dirent.h>
#include "Options.hpp"
#include "Character.hpp"

namespace is
{
    enum class poweris : int {
        POWERLIVE = 0,
        POWERBOMB,
        POWERPOWER
    };

    class Character;
    class map;
    class PowerUp
            : public __gnu_cxx::__normal_iterator<::std::shared_ptr<::is::PowerUp> *, ::std::vector<::std::shared_ptr<::is::PowerUp>>> {
    public:
        PowerUp(irr::scene::IAnimatedMesh *,
                 irr::video::ITexture *,
                 irr::scene::ISceneManager &,
                 irr::core::vector3df const &,
                is::map                     *);
        ~PowerUp();
        bool    check(irr::core::vector3df const &);
        void    getPower(is::Character *);
    private:

        irr::scene::IAnimatedMeshSceneNode  *_mesh;
        irr::video::ITexture                *_text;
        irr::scene::ISceneManager           &_smgr;
        irr::core::vector3df                _posMap;
        irr::core::vector3df                _posSpace;
        irr::scene::IAnimatedMesh           *_node;
        is::map                             *_map;
        is::poweris                         _power;
    };
}

#endif //MAP_POWERUP_HPP
