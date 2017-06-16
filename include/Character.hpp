//
// Created by kyxo on 5/30/17.
//

#ifndef CPP_INDIE_STUDIO_CHARACTER_HPP
#define CPP_INDIE_STUDIO_CHARACTER_HPP

#include <string>
#include <math.h>
#include "Options.hpp"
#include "BombsManager.hpp"
#include "GameEventReceiver.hpp"

using namespace irr;

#define DEFAULT_SPEED 2
#define DEFAULT_POWER 1
#define DEFAULT_BOMB 1

namespace  is
{
  class Character
  {
    enum class DIR : irr::u8
    {
      LEFT = 0,
      RIGHT,
      TOP,
      DOWN
    };
   public:
    Character(scene::IAnimatedMesh *node, video::ITexture *texture, scene::ISceneManager *smgr,
	      core::vector3df const &pos, const GameEventReceiver &receiver, const Options &opt,
	      BombsManager &bombsManager);
    ~Character() {}
    void 	moove();
      void  incLive() {_live += 1;}
    irr::core::vector3df    			&getPos(){return _pos;}
    scene::IAnimatedMeshSceneNode 		*_mesh;
   private:
    video::ITexture 				*_text;
    scene::ISceneManager 			*_smgr;
    core::vector3df 				_pos;
    int _speed;
    int _bomb;
    int _power;
    int _live;
    const GameEventReceiver 			&_receiver;
    const Options				&_opt;
    DIR						_dir;
    BombsManager &_bombsManager;
    bool 					_keySlow;

  };
}

#endif //CPP_INDIE_STUDIO_CHARACTER_HPP