//
// Created by vincent on 12/06/17.
//

#ifndef MAP_BOMBST_HPP
#define MAP_BOMBST_HPP

#include <thread>
#include <functional>
#include "map.hpp"
#include "Bomb.hpp"

namespace is
{
  class BombsManager
  {
   public:
    BombsManager(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager);
    ~BombsManager();

    void 			putBomb(const irr::core::vector3df &pos, int power);

   private:
    is::map					&_map;
    irr::video::IVideoDriver			&_videoDriver;
    irr::scene::ISceneManager			&_sceneManager;
    irr::video::ITexture 			*_texture;
    irr::scene::IAnimatedMesh 			*_mesh;
    std::vector<std::thread>			_threads;
    std::vector<is::Bomb>			_bombs;
    std::function<void(is::Bomb &,
		       std::vector<std::thread> &,
		       std::vector<is::Bomb> &)> 		_explosion;
    std::mutex					_bomb_mutex;
  };
}

#endif //MAP_BOMBST_HPP
