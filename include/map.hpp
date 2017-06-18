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
#include "PowerUpManager.hpp"

# define SCALE	15
# define BLOCK	15

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
  class PowerUpManager;
  class map
  {
   public:
    map(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr, std::vector<int> &map);
    virtual ~map();
    void		moveObject(Block &object, Vector3d const &pos);
    int 		addObject(Type type, Vector3d const &);
    void		delObject(Block &object);
    void 		delObject(Vector3d const &pos);
    bool 		canIMoove(Vector3d const &pos) const;
    bool 		canIMoove2(Vector3d const &pos) const;
    int         getLocalType(Vector3d const &pos) const;
    int 		find(Vector3d const &v) const;
    Block const		*findBlock(Vector3d const &v) const;
    int			find(Block const &b) const;
    void		initEffects();
    void		addCollision(irr::scene::ISceneNode *);
    void		draw();
    void 		printMap();

   private:
    irr::scene::ISceneManager *_smgr;
    irr::video::IVideoDriver *_driver;
    std::vector<Block> 						_mapi;
    std::vector<int>						&_map;
    irr::video::ITexture 						*_texture[Type::NBR_OF_TYPE];
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
    is::PowerUpManager                      *_pm;
  public:
      void set_pm(is::PowerUpManager *_pm);
  };
}

#endif //CPP_INDIE_STUDIO_MAP_HPP
