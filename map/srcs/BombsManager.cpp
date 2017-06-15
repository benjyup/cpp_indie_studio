//
// Created by vincent on 12/06/17.
//

#include <iostream>
#include <thread>
#include "Game.hpp"
#include "BombsManager.hpp"
#include "Fire.hpp"
#include "../../src/IndieStudioException.hpp"

is::BombsManager::BombsManager(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager) :
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager),
	_texture(NULL),
	_mesh(this->_sceneManager.getMesh("./gfx/bomb.obj"))

{
}

is::BombsManager::~BombsManager()
{

}

void is::BombsManager::putBomb(const irr::core::vector3df &pos, int power)
{
  this->_bombs.push_back(std::make_shared<Bomb>(this->_map, this->_texture, this->_mesh, pos, power, this->_videoDriver, this->_sceneManager));
}

bool is::BombsManager::checkBombsStatus()
{
  bool 		ret = false;

  this->_bombs.erase(std::remove_if(this->_bombs.begin(), this->_bombs.end(),
				    [&ret](auto bomb) {
				      ret = true;
				      return bomb->blowUp();
				    }),
		     this->_bombs.end());
  return (ret);
}
