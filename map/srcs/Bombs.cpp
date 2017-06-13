//
// Created by vincent on 12/06/17.
//

#include <iostream>
#include <thread>
#include "Bombs.hpp"
#include "Fire.hpp"
#include "../../src/IndieStudioException.hpp"

is::Bombs::Bombs(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager) :
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager),
	_texture(NULL),
	_mesh(this->_sceneManager.getMesh("./gfx/bomb.obj"))

{
  this->_explosion = [&](is::Bomb &bomb) {
    std::this_thread::sleep_for(std::chrono::operator""ms(5000));
    bomb.blowUp();
  };
}

is::Bombs::~Bombs()
{
  for (auto &t : this->_threads)
    t.join();
}

void is::Bombs::putBomb(const irr::core::vector3df &pos, int power)
{
//  this->_threads.emplace_back(this->_explosion, pos, power);

  this->_bombs.emplace_back(this->_map, this->_texture, this->_mesh, pos, power, this->_videoDriver, this->_sceneManager);
  this->_threads.emplace_back(this->_explosion, std::ref(this->_bombs.back()));
}

int 			is::Bombs::reducePower(irr::core::vector3df pos,
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
