//
// Created by vincent on 17/06/17.
//

#ifndef CPP_INDIE_STUDIO_CHOOSEPLAYER_HPP
#define CPP_INDIE_STUDIO_CHOOSEPLAYER_HPP

#include <array>
#include "irrlicht.h"
#include "IGameState.hpp"
#include "Options.hpp"
#include "Button.hpp"

namespace is
{
  class ChoosePlayerState : public IGameState
  {
   public:
    ChoosePlayerState();
    ~ChoosePlayerState();

    virtual void Init(GameEngine *engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void Resume(void);
    virtual void HandleEvents(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void ChangeState(GameEngine *engine, IGameState *state);

   private:
    Options			*_options;
    irr::gui::IGUIEnvironment	*_gui;
    irr::video::IVideoDriver	*_driver;
    std::vector<is::Button>	_buttons;
  };
}

#endif //CPP_INDIE_STUDIO_CHOOSEPLAYER_HPP
