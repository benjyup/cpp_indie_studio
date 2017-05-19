//
// Created by vincent on 11/05/17.
//

#ifndef CPP_INDIE_STUDIO_GAMESTATE_HPP
#define CPP_INDIE_STUDIO_GAMESTATE_HPP

#include "IGameState.hpp"
#include "irrlicht.h"

namespace is {
  class GameState : public IGameState
  {
   public:
    GameState(void);
    virtual ~GameState(void);

    virtual void 	Init(GameEngine *game);
    virtual void 	Cleanup(void);
    virtual void 	Pause(void);
    virtual void 	Resume(void);
    virtual void 	HandleEvents(GameEngine *game);
    virtual void 	Update(GameEngine *game);
    virtual void 	Draw(GameEngine *game);
    virtual void 	ChangeState(GameEngine *game, IGameState *state);

   private:
  };
}

#endif //CPP_INDIE_STUDIO_GAMESTATE_HPP
