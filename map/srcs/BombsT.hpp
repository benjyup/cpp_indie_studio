//
// Created by vincent on 12/06/17.
//

#ifndef MAP_BOMBST_HPP
#define MAP_BOMBST_HPP

#include <thread>
#include <functional>
#include "map.hpp"

namespace is
{
  class BombsT
  {
   public:
    BombsT(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager);
    ~BombsT();

    void 			putBomb(const irr::core::vector3df &pos, int power);

   private:
    is::map					&_map;
    irr::video::IVideoDriver			&_videoDriver;
    irr::scene::ISceneManager			&_sceneManager;
    std::vector<std::thread>			_bombs;
    std::function<void(const irr::core::vector3df &, int)> 	_explosion;

    int 					reducePower(irr::core::vector3df pos,
							   int power,
							   const std::function<void(irr::core::vector3df &)> &callback);
  };
}

#endif //MAP_BOMBST_HPP
