//
// Created by rene_r on 6/13/17.
//

#pragma once

#include "Character.hpp"
#include "../LuaBridge/Source/LuaBridge/LuaBridge.h"

namespace is
{
  class Ia;
  
  enum STRAT
    {
      ATTACK,
      HIDE,
      WAIT
    };
  class Strategy
  {
    is::Character::DIR		_dir;
    irr::core::vector3df	_pos;
    is::Ia		       *_ia;
    luabridge::LuaRef     _action;
    std::string name;
    luabridge::lua_State	*_L;
    bool			_open;
    //    std::unique_ptr<luabridge::LuaRef> interactFunc;
  public:
    Strategy(luabridge::lua_State	*L, const std::string &, Ia *);
    ~Strategy();
    int loadScript(STRAT);
    void loadScript(luabridge::lua_State* L, const std::string& scriptFilename);
    void goToDir(is::Character::DIR);
    
    void choseNextDir();
    void defineDir();
    void go();
    void move();
    void Allo(std::string const &);
  };

};
