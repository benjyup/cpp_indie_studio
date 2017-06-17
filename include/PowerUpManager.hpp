//
// Created by Jean-Adrien on 13/06/17.
//

#ifndef MAP_POWERUPMANAGER_HPP
#define MAP_POWERUPMANAGER_HPP

#include <vector>
#include <memory>
#include "PowerUp.hpp"

namespace is {
    class PowerUpManager {
    public:
        PowerUpManager(irr::scene::ISceneManager &, irr::video::IVideoDriver &, is::map *);
        ~PowerUpManager() {};

        void    newPow(irr::core::vector3df const &);
    private:
        irr::scene::ISceneManager                   &_sceneManager;
        irr::video::IVideoDriver                    &_driver;
        std::vector<std::shared_ptr<is::PowerUp>>   _powUp;
        is::map                                     *_map;
    };
}

#endif //MAP_POWERUPMANAGER_HPP
