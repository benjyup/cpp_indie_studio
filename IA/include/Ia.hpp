//
// Created by rene_r on 6/12/17.
//

#pragma once

#include "Character.hpp"
#include "Strategy.hpp"
#include "../LuaBridge/Source/LuaBridge/LuaBridge.h"

namespace is
{
  class Ia: public Character 
  {
    bool			_danger;
    luabridge::lua_State	*_L;

    std::vector<Strategy *>	_theStrats;//les stratégies

  public:
    Ia(scene::IAnimatedMesh *, video::ITexture *, scene::ISceneManager *,
       core::vector3df const &, const GameEventReceiver &, const Options &,
       BombsManager &bombsManager);
    ~Ia();
    bool		isInDanger();
    void		Allo(std::string const &);
    void		hideHilself();
    core::vector3df	findPlaceForBomb();
    core::vector3df	findEnnemy();
    core::vector3df	findPowerUp();
    void		changeDir(DIR);
    void		construct_L();
    virtual void	        move();
  };
};