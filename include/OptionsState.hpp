//
// Created by vincent on 23/05/17.
//

#pragma once

#include <map>
#include <IGameState.hpp>
#include "MenuState.hpp"
#include "OptionsEventReceiver.hpp"

class OptionsEventReceiver;

namespace is
{
  class OptionsState : public MenuState
  {
   public:

    OptionsState();
    virtual ~OptionsState();
    virtual void 					Init(is::GameEngine *engine);
    virtual void 					Resume(void);
    virtual void 					HandleEvents(void);
   private:
    CHANGE 						_change;
    OptionsEventReceiver				                _optionsEventReceiver;
  };
}
