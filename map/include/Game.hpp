//
// Created by kyxo on 5/24/17.
//

#ifndef CPP_INDIE_STUDIO_GAME_HPP
#define CPP_INDIE_STUDIO_GAME_HPP


#pragma once

#include <vector>
#include <iostream>
#include <srcs/BombsT.hpp>
#include "IGameState.hpp"
#include "GameEventReceiver.hpp"
#include "map.hpp"
#include "ParseMap.hpp"
#include "Bombs.hpp"

namespace is
{
  class Game : public IGameState
  {
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
    ParseMap	    				_parserMap;
    irr::video::IVideoDriver			*_driver;
    irr::scene::ISceneManager			*_sceneManager;
    irr::gui::IGUIEnvironment			*_gui;
    GameEngine 					*_engine;
    std::shared_ptr<map>			_map;
    std::shared_ptr<Bombs>			_bomb;
    std::shared_ptr<BombsT>			_bombs;
    std::array<std::shared_ptr<Character>, 2>	_char;
    Options					_opt;
    GameEventReceiver				_receiver;
  };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP