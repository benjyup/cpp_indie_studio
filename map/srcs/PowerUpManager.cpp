//
// Created by alice on 13/06/17.
//

#include <iostream>
#include <include/map.hpp>
#include "PowerUpManager.hpp"

is::PowerUpManager::PowerUpManager(irr::scene::ISceneManager &sceneManager,
                                   irr::video::IVideoDriver &driver,
                                    is::map                  *map) : _sceneManager(sceneManager),
                                                                     _driver(driver),
                                                                     _map(map)
{
    std::cout << "Indie_studio: PowerUpManager _initializated" << std::endl;
}

void is::PowerUpManager::newPow() {
    _powUp.push_back(std::make_shared<is::PowerUp>(PowerUp((_sceneManager.getMesh("./powersUp/mushroom/supermushroom.obj")),
                                                           _driver.getTexture("./powersUp/mushroom/t0081_0.png"),
                                                           _sceneManager, irr::core::vector3df(7, 7, 0), _map)));
}
