//
// Created by kyxo on 5/23/17.
//

#ifndef CPP_INDIE_STUDIO_BLOCK_HPP
#define CPP_INDIE_STUDIO_BLOCK_HPP

#include <irrlicht.h>
#include "map.hpp"

using namespace irr;

namespace is
{
  enum Type : int{
    GRASS = 0,
    WALL,
    BREAK
  };

  class Block
  {
   public:
    Block(Vector3d const & pos);
    ~Block();
    void   init(Type t, video::ITexture *text, int size);
    Block 	&operator=(Block const &);
   private:
    friend class map;
    scene::IAnimatedMeshSceneNode	*node;
    Vector3d				pos;
    Type 				type;
  };
}

#endif //CPP_INDIE_STUDIO_BLOCK_HPP
