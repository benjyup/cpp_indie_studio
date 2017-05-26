//
// Created by kyxo on 5/24/17.
//

#ifndef CPP_INDIE_STUDIO_GAME_HPP
#define CPP_INDIE_STUDIO_GAME_HPP


#pragma once

#include <vector>
#include <iostream>
#include "IGameState.hpp"
#include "map.hpp"
#include "ParseMap.hpp"
#include "Bombs.hpp"

namespace is
{
  class Game : public IGameState
  {
    ParseMap	    _parserMap;
   public:
    Game();
    virtual ~Game();
    virtual void Init(GameEngine *engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void Resume(void);
    virtual void HandleEvents(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void ChangeState(GameEngine *engine,
			     IGameState *state);
   private:
    irr::video::IVideoDriver			*_driver;
    irr::scene::ISceneManager			*_sceneManager;
    irr::gui::IGUIEnvironment			*_gui;
    GameEngine 					*_engine;
    std::shared_ptr<map>			_map;
    std::shared_ptr<Bombs>			_bomb;
  };
}


#endif //CPP_INDIE_STUDIO_GAME_HPP
