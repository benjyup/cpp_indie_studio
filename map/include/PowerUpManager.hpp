//
// Created by alice on 13/06/17.
//

#ifndef MAP_POWERUPMANAGER_HPP
#define MAP_POWERUPMANAGER_HPP

#include <vector>
#include <memory>
#include "PowerUp.hpp"

namespace is {
    class PowerUpManager {
    public:
        PowerUpManager(irr::scene::ISceneManager &, irr::video::IVideoDriver &);
        ~PowerUpManager() {};

        void    newPow(void);
        void    update(irr::core::vector3df &pos);
    private:
        irr::scene::ISceneManager                   &_sceneManager;
        irr::video::IVideoDriver                    &_driver;
        std::vector<std::shared_ptr<is::PowerUp>>   _powUp;
    };
}

#endif //MAP_POWERUPMANAGER_HPP
