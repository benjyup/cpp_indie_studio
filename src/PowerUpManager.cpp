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
                                                                     _map(map)
{
    _mesh.push_back(_sceneManager.getMesh("./powersUp/mushroom/supermushroom.obj"));
    _mesh.push_back(_sceneManager.getMesh("./powersUp/battery/WindBomb.obj"));
    _mesh.push_back(_sceneManager.getMesh("./powersUp/bomb/LightBomb.obj"));
    _texture.push_back(_driver.getTexture("./powersUp/mushroom/t0081_0.png"));
    _texture.push_back(_driver.getTexture("./powersUp/battery/texture.png"));
    _texture.push_back(_driver.getTexture("./powersUp/bomb/texture.png"));

    std::cout << "Indie_studio: PowerUpManager _initializated" << std::endl;
}

void is::PowerUpManager::newPow(irr::core::vector3df const &map) {
    int prob = std::rand() % 2;
    if (prob != 0)
        return;
    int type = std::rand() % 3;
    _powUp.emplace_back(std::make_shared<is::PowerUp>(_mesh[type],
                                                      _texture[type],
                                                      _sceneManager, map, _map, static_cast<is::poweris>(type)));
}

void is::PowerUpManager::getPowerUp(irr::core::vector3df const &pos) {
  _powUp.erase(std::remove_if(_powUp.begin(), _powUp.end(), [pos](auto powUp) {
    return (powUp->check(pos));
  }));
}

void is::PowerUpManager::getPower(is::Character &c, irr::core::vector3df const &pos) {
    is::poweris power;
    for (auto &ref : _powUp)
    {
        if (ref->check(pos))
            power = ref->getType();
    }
    switch (power) {
        case is::poweris::POWERLIVE:
            c.incLive();
            break;
        case is::poweris::POWERBOMB:
            c.incbomb();
            break;
        case is::poweris::POWERPOWER:
            c.incPower();
            break;
        };
}
