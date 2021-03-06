//
// greg
//

#pragma once

#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
#include "GameEngine.hpp"
#include "ParseMap.hpp"
#include "map.hpp"
#include "GenerateMap.hpp"
#include "Camera.hpp"
#include "Fire.hpp"
#include "PlanetSystem.hpp"
#include "IntroEventReceiver.hpp"

namespace is
{
  class                       IntroState : public IGameState
  {
   public:
    IntroState();
    virtual                 ~IntroState();
    virtual void            Init(GameEngine *engine);
    virtual void            Cleanup();
    virtual void            Pause();
    virtual void            Resume();
    virtual void            HandleEvents();
    virtual void            Update();
    virtual void            Draw();
    virtual void            ChangeState(GameEngine *engine, IGameState *state);
   private:
    CHANGE 						_change;
    GameEngine                                        *_engine;
    irr::video::IVideoDriver			              *_driver;
    irr::scene::ISceneManager			              *_sceneManager;
    std::vector<int>                                  _mapi;
    ParseMap	    				                  _parserMap;
    std::shared_ptr<map>			                  _map;
    IntroEventReceiver                                _introEventReceiver;
    Camera					*_cam;
  };
}