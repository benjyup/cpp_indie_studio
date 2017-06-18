//
// Created by vincent on 12/06/17.
//

#ifndef MAP_BOMBST_HPP
#define MAP_BOMBST_HPP

#include <thread>
#include <functional>
#include <list>
#include "map.hpp"
#include "Bomb.hpp"

namespace is
{
  class Character;
  class BombsManager
  {
   public:
    BombsManager(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager, is::PowerUpManager &pm);
    ~BombsManager();

    void 			putBomb(const irr::core::vector3df &pos, int power);
    bool 			checkBombsStatus(std::list<std::shared_ptr<is::Character>> const &Char);
    void addCollision(std::list<std::shared_ptr<is::Character>> const &Char);

   private:
    is::map					&_map;
    irr::video::IVideoDriver			&_videoDriver;
    irr::scene::ISceneManager			&_sceneManager;
    irr::video::ITexture 			*_texture;
    irr::scene::IAnimatedMesh 			*_mesh;
    irr::scene::IAnimatedMesh 			*_mesh2;
    std::list<std::shared_ptr<is::Bomb>>	_bombs;
    std::function<void(is::Bomb &,
		       std::vector<std::thread> &,
		       std::vector<is::Bomb> &)> 		_explosion;
    std::mutex					_bomb_mutex;
    is::PowerUpManager                  &_pm;
    std::map<unsigned int, irr::scene::ITriangleSelector *>	_col;
    std::map<unsigned int, irr::scene::IMeshSceneNode *>	_colNode;

    bool checkChar(std::list<std::shared_ptr<Character>> const &Char, irr::core::vector3df const &v);

  };
}

#endif //MAP_BOMBST_HPP
