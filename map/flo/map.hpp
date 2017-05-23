//
// Created by kyxo on 5/22/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include "Vector3d.hpp"
#include <vector>
#include <irrlicht.h>

# define SCALE 140

using namespace irr;

namespace is
{
  class map
  {
   public:
    map(video::IVideoDriver *driver, scene::ISceneManager *smgr, std::vector<int> &map);
    ~map() {}
    void		moveObject(scene::IAnimatedMeshSceneNode *object,
				   	Vector3d const &pos);
    void		delObject(scene::IAnimatedMeshSceneNode *object);
    int			find(scene::IAnimatedMeshSceneNode *object);
    void		burn(Vector3d const &v, int level);
    void		fire_up(Vector3d const &v, int level);

   private:
    scene::ISceneManager *_smgr;
    video::IVideoDriver *_driver;
    std::vector<scene::IAnimatedMeshSceneNode *> _mapi;
    std::vector<int>						&_map;
    video::ITexture 						*_texture[4];
    int 							size;
  };
}


#endif //CPP_INDIE_STUDIO_MAP_HPP
