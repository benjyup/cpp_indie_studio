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
#include "PowerUpManager.hpp"

#define DEFAULT_SPEED 1.2
#define DEFAULT_POWER 1
#define DEFAULT_BOMB 1

namespace  is
{
    class PowerUpManager;
    class BombsManager;
    class map;

  class Character
  {
    enum class DIR : irr::u8
    {
      LEFT = 0,
      RIGHT,
      TOP,
      DOWN,
      NONE
    };
    enum class STATE : irr::u8
    {
      ALIVE = 0,
      DYING,
      DEAD
    };
   public:
    Character(irr::scene::IAnimatedMesh *node, irr::video::ITexture *texture, irr::scene::ISceneManager *smgr,
	      irr::core::vector3df const &pos, const GameEventReceiver &receiver, std::map<Options::MOVES, irr::EKEY_CODE>  const &Config,
	      BombsManager &bombsManager, int id);
    ~Character() {}
    void 	moove();
    void  incSpeed();
    void    incbomb();
    void    incPower();
    void   update(is::PowerUpManager *, is::map *);
    irr::core::vector3df    			const &getPos() const;
    irr::scene::ISceneNode 		*getMesh();
    bool 					getAlive();
    void					die();
    void					pushAnim(irr::scene::ISceneNodeAnimator *, unsigned int);
    irr::scene::ISceneNodeAnimator		*getAnim(unsigned int);
    float           getSpeed() const;
    int           getBomb() const;
    int           getPower() const;
    int						getId();

   private:
    irr::scene::IAnimatedMeshSceneNode 		*_mesh;
    irr::video::ITexture 				*_text;
    irr::scene::ISceneManager 			*_smgr;
    irr::core::vector3df 				_pos;
    float _speed;

    int _bomb;
    int _power;
    const GameEventReceiver 			&_receiver;
    DIR						_dir;
    BombsManager &_bombsManager;
    bool 					_keySlow;
    const std::map<Options::MOVES, irr::EKEY_CODE> 	&_Config;
    STATE 						_state;
    char 						_animDie;
    int 					_id;
    std::map<unsigned int, irr::scene::ISceneNodeAnimator *>	_anim;
  };
}

#endif //CPP_INDIE_STUDIO_CHARACTER_HPP