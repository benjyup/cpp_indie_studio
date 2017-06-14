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
  this->_explosion = [&](is::Bomb &bomb, std::vector<std::thread> &threads, std::vector<is::Bomb> &bombs) {
      std::this_thread::sleep_for(std::chrono::operator ""ms(5000));
    {
      bomb.blowUp();
    }

//    std::unique_lock<std::mutex> lock2(this->_bomb_mutex);
    auto thread_it = threads.begin();
    for (auto bomb_it = bombs.begin() ; bomb_it != bombs.end() ; ++bomb_it)
      {
	if (*bomb_it == bomb)
	  {
	    bombs.erase(bomb_it);
	    thread_it->detach();
	    threads.erase(thread_it);
	    return ;
	  }
      }
    //bombs.erase(std::find(bombs.begin(), bombs.end(), bomb));
  };
}

is::BombsManager::~BombsManager()
{
  for (auto &t : this->_threads)
    t.join();
}

void is::BombsManager::putBomb(const irr::core::vector3df &pos, int power)
{
//  this->_threads.emplace_back(this->_explosion, pos, power);

  this->_bombs.emplace_back(this->_map, this->_texture, this->_mesh, pos, power, this->_videoDriver, this->_sceneManager);

  this->_threads.emplace_back(this->_explosion, std::ref(this->_bombs.back()), std::ref(this->_threads), std::ref(this->_bombs));
}
