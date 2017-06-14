//
// Created by alice on 13/06/17.
//

#include <iostream>
#include "PowerUpManager.hpp"

is::PowerUpManager::PowerUpManager(irr::scene::ISceneManager &sceneManager,
                                   irr::video::IVideoDriver &driver) : _sceneManager(sceneManager),
                                                                        _driver(driver)
{
    std::cout << "Indie_studio: PowerUpManager _initializated" << std::endl;
}

void is::PowerUpManager::newPow() {
    _powUp.push_back(std::make_shared<is::PowerUp>(PowerUp((_sceneManager.getMesh("./powersUp/mushroom/supermushroom.obj")),
                                                           _driver.getTexture("./powersUp/mushroom/t0081_0.png"),
                                                           _sceneManager, irr::core::vector3df(100, 0, 100))));
    _powUp.push_back(std::make_shared<is::PowerUp>(PowerUp((_sceneManager.getMesh("./gfx/plan-2.obj")),
                                                           _driver.getTexture("./gfx/blocks1.jpg"),
                                                           _sceneManager, irr::core::vector3df(100, 0, 100))));
}

void is::PowerUpManager::update(irr::core::vector3df &pos) {
    _powUp[0]->update(pos);
}