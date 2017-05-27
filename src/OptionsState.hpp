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

   private:
    static const std::vector<irr::core::stringw>	NAME_OF_ACTIONS;
    Options						_options;
    OptionsEventReceiver				_optionsEventReceiver;
    OptionsEventReceiver::SOptionsContext		_optionsContext;

    void 						drawNameActions();
    std::map<Options::MOVES, irr::EKEY_CODE>		getPlayerConfig(irr::s8 player);
  };
}
