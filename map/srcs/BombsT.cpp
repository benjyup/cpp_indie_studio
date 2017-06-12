//
// Created by vincent on 12/06/17.
//

#include <iostream>
#include <thread>
#include "BombsT.hpp"

is::BombsT::BombsT(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager) :
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager)
{
  this->_explosion = [&](const irr::core::vector3di &pos, int power) {
    std::this_thread::sleep_for(std::chrono::operator""ms(2000));
    auto *texture = this->_videoDriver.getTexture("./gfx/Bomb.png");
    irr::scene::IAnimatedMesh *bombMesh = this->_sceneManager.getMesh("./gfx/bomb.obj");
    irr::scene::IAnimatedMeshSceneNode *msn = this->_sceneManager.addAnimatedMeshSceneNode(bombMesh);

    msn->setPosition({0, 2 * SCALE, 0});
    msn->setScale({SCALE, SCALE, SCALE});
    msn->setMaterialTexture(0, texture);

    std::cout << "Bomb posée" << std::endl;
    std::this_thread::sleep_for(std::chrono::operator""ms(2000));
    std::cout << "Bomb explose" << std::endl;
  };
}

is::BombsT::~BombsT()
{

}

void is::BombsT::putBomb(const irr::core::vector3di &pos, int power)
{
  this->_bombs.emplace_back(this->_explosion, pos, power);
}
