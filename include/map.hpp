//
// Created by kyxo on 5/22/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include <vector>
#include <irrlicht.h>
#include <memory>
#include "Vector3d.hpp"
#include "Fire.hpp"
#include "Block.hpp"
#include "PlanetSystem.hpp"

# define SCALE	15
# define BLOCK	15

using namespace irr;

enum Type : int;

class Fire;

namespace is
{

  enum Type : int{
    GRASS = 0,
    WALL,
    BREAK,
    FIRE,
    BOMB,
    POWERUP,
    NBR_OF_TYPE
  };

  class Block;
  class map
  {
   public:
    map(video::IVideoDriver *driver, scene::ISceneManager *smgr, std::vector<int> &map);
    virtual ~map();
    void		moveObject(Block &object, Vector3d const &pos);
    void		addObject(Type type, Vector3d const &);
    void		delObject(Block &object);
    void 		delObject(Vector3d const &pos);
    bool 		canIMoove(Vector3d const &pos) const;
    bool 		canIMoove2(Vector3d const &pos) const;
    int 		find(Vector3d const &v) const;
    Block const		*findBlock(Vector3d const &v) const;
    int			find(Block const &b) const;
    void		initEffects();
    void		addCollision(scene::ISceneNode *);
    void		draw();


   private:
    scene::ISceneManager *_smgr;
    video::IVideoDriver *_driver;
    std::vector<Block> 						_mapi;
    std::vector<int>						&_map;
    video::ITexture 						*_texture[Type::NBR_OF_TYPE];
    int 							size;
    std::vector<irr::scene::ITriangleSelector *>		_t;

    std::shared_ptr<Fire>			            	_fire1;
    std::shared_ptr<Fire>			            	_fire2;
    std::shared_ptr<Fire>			            	_fire3;
    std::shared_ptr<Fire>			            	_fire4;
    std::shared_ptr<PlanetSystem>				_planetR;
    std::shared_ptr<PlanetSystem>				_planetW;
    std::shared_ptr<PlanetSystem>				_planetG;
    irr::scene::ISceneNode					*_skyUp;
    irr::scene::ISceneNode					*_skyDown;
  };
}

#endif //CPP_INDIE_STUDIO_MAP_HPP