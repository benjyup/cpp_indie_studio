//
// Created by kyxo on 5/22/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include <vector>
#include <irrlicht.h>
#include "Vector3d.hpp"
#include "Block.hpp"

# define SCALE 10

using namespace irr;

namespace is
{
  class Block;
  class map
  {
   public:
    map(video::IVideoDriver *driver, scene::ISceneManager *smgr, std::vector<int> &map);
    ~map() {}
    void		moveObject(Block &object, Vector3d const &pos);
    void		addObject(int type, Vector3d const &);
    void		delObject(Block &object);
    bool 		canIMoove(Vector3d const &pos) const;
    int 		find(Vector3d const &v) const;
    int			find(Block const &b) const;

  private:
    scene::ISceneManager *_smgr;
    video::IVideoDriver *_driver;
    std::vector<Block> 	_mapi;
    std::vector<int>						&_map;
    video::ITexture 						*_texture[4];
    int 							size;
  };
}


#endif //CPP_INDIE_STUDIO_MAP_HPP
