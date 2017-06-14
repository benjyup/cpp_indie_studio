//
// Created by vincent on 13/06/17.
//

#ifndef MAP_BOMB_HPP
#define MAP_BOMB_HPP


#include <ITexture.h>
#include <thread>
#include <mutex>
#include "map.hpp"
#include "IndieStudioException.hpp"
#include "Fire.hpp"
#include "map.hpp"

namespace is
{

  class Bomb
  {
   public:
    Bomb(map &map, irr::video::ITexture *texture, irr::scene::IAnimatedMesh *bombMesh,
	 const irr::core::vector3df &posMap, int power,
	 irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager);

    ~Bomb();

    void draw();

    void remove();

    void blowUp();

    int reducePower(irr::core::vector3df pos,
		    int power,
		    const std::function<void(irr::core::vector3df &)> &callback);


   private:
    irr::core::vector3df _posMap;
    irr::core::vector3df _posSpace;
    int _power;
    is::map &_map;
    irr::video::IVideoDriver &_videoDriver;
    irr::scene::ISceneManager &_sceneManager;
    irr::scene::IAnimatedMeshSceneNode *_node;
  };
}

#endif //MAP_BOMB_HPP
