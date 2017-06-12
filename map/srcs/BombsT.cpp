//
// Created by vincent on 12/06/17.
//

#include <iostream>
#include <thread>
#include "BombsT.hpp"
#include "Fire.hpp"

is::BombsT::BombsT(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager) :
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager)
{
  this->_explosion = [&](const irr::core::vector3df &pos, int power) {

    //auto *texture = this->_videoDriver.getTexture("./gfx/Bomb/bomb.png");
    irr::scene::IAnimatedMesh *bombMesh = this->_sceneManager.getMesh("./gfx/Bomb.obj");
    irr::scene::IAnimatedMeshSceneNode *msn = this->_sceneManager.addAnimatedMeshSceneNode(bombMesh);
    if (bombMesh == NULL)
      std::cout << "!bombMesh" <<std::endl;
    if (bombMesh == NULL)
      std::cout << "!msn" <<std::endl;

    irr::core::vector3df posSpace(pos.Y * SCALE - SCALE / 2, 10, pos.X * SCALE + SCALE / 2);
    msn->setPosition(posSpace);
    msn->setScale({5, 5, 5});
    msn->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);

    //std::this_thread::sleep_for(std::chrono::operator""ms(2000));

    irr::core::vector3df posMap(pos.X, pos.Y, pos.Y);
    std::cout << "ici" << std::endl;

/*
    Fire fire_forward(&this->_sceneManager, &this->_videoDriver, posSpace, FireDirection::FORWARD,
		      this->reducePower(posMap, power, [](irr::core::vector3df &pos) {pos.Z += 1;}));
*/

    std::cout << "ici" << std::endl;
/*
    //Fire fire_forwardd(&this->_sceneManager, &this->_videoDriver, p, FireDirection::RIGHT, 2);
*/
    posMap = irr::core::vector3df(pos.X, pos.Y, pos.Y);
    Fire fire_backward(&this->_sceneManager, &this->_videoDriver, posSpace, FireDirection::RIGHT,
	    this->reducePower(posMap, power, [&](irr::core::vector3df &pos) {pos.Z += 1;}));

/*
    posMap = irr::core::vector3df(pos.X, pos.Y, pos.Y);
    Fire fire_right(&this->_sceneManager, &this->_videoDriver, posSpace, FireDirection::RIGHT,
	    this->reducePower(posMap, power, [&](irr::core::vector3df &pos) {pos.X -= 1;}));
*/
/*
    Fire fire_left(&this->_sceneManager, &this->_videoDriver, p, FireDirection::LEFT,
	    this->reducePower(p, 2, [&](irr::core::vector3df &pos) {pos.X -= 1;}));
*/

    std::cout << "Bomb posée" << std::endl;
    std::this_thread::sleep_for(std::chrono::operator""ms(20000));
    std::cout << "Bomb explose" << std::endl;

    msn->remove();
  };
}

is::BombsT::~BombsT()
{
  for (auto &t : this->_bombs)
    t.join();
}

void is::BombsT::putBomb(const irr::core::vector3df &pos, int power)
{
  this->_bombs.emplace_back(this->_explosion, pos, power);
}

int 			is::BombsT::reducePower(irr::core::vector3df pos,
						   int power,
						   const std::function<void(irr::core::vector3df &)> &callback)
{
  int			ret = 0;

  callback(pos);
  while (this->_map.canIMoove2(is::Vector3d(pos.X, pos.Z, pos.Z)) && ret < power)
    {
      std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      callback(pos);
      std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      ret += 1;
    }
  std::cout << "ret = " << ret << std::endl;
  return ret;
}