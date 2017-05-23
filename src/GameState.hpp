//
// Created by vincent on 11/05/17.
//

#ifndef CPP_INDIE_STUDIO_GAMESTATE_HPP
#define CPP_INDIE_STUDIO_GAMESTATE_HPP

#include <memory>
#include "IGameState.hpp"
#include "irrlicht.h"

namespace is {
  class GameState : public IGameState
  {
  public:
    GameState(void);
    virtual ~GameState(void);

    virtual void 	Init(GameEngine *engine);
    virtual void 	Cleanup(void);
    virtual void 	Pause(void);
    virtual void 	Resume(void);
    virtual void 	HandleEvents(void);
    virtual void 	Update(void);
    virtual void 	Draw(void);
    virtual void 	ChangeState(GameEngine *engine, IGameState *state);

  private:
    GameEngine 		*_engine;
  };
}

#endif //CPP_INDIE_STUDIO_GAMESTATE_HPP
