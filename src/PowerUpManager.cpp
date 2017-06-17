//
// Created by Jean-Adrien on 13/06/17.
//

#include <iostream>
#include <map.hpp>
#include "PowerUpManager.hpp"

is::PowerUpManager::PowerUpManager(irr::scene::ISceneManager &sceneManager,
                                   irr::video::IVideoDriver &driver,
                                    is::map                  *map) : _sceneManager(sceneManager),
                                                                     _driver(driver),
                                                                     _map(map),
                                                                     _mesh(_sceneManager.getMesh("./powersUp/mushroom/supermushroom.obj")),
                                                                     _texture(_driver.getTexture("./powersUp/mushroom/t0081_0.png"))
{
    std::cout << "Indie_studio: PowerUpManager _initializated" << std::endl;
}

void is::PowerUpManager::newPow(irr::core::vector3df const &map) {
    _powUp.emplace_back(std::make_shared<is::PowerUp>(_mesh,
                                                      _texture,
                                                      _sceneManager, map, _map));
}

void is::PowerUpManager::getPowerUp(irr::core::vector3df const &pos) {
  _powUp.erase(std::remove_if(_powUp.begin(), _powUp.end(), [pos](auto powUp) {
    return (powUp->check(pos));
  }));
}
