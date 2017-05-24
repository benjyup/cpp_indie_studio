//
// Created by vincent on 23/05/17.
//

#pragma once

#include <map>
#include <IGameState.hpp>
#include "MenuState.hpp"
#include "OptionsEventReceiver.hpp"

namespace is
{
  class OptionsState : public MenuState
  {
   public:
    enum class GUI_ID_BOUTON : irr::s32
    {
      GUI_ID_MOVE_ACTION_BUTTON = 0,
      GUI_ID_MOVE_FORWARD_BUTTON,
      GUI_ID_MOVE_BACKWARD_BUTTON,
      GUI_ID_MOVE_RIGHT_BUTTON,
      GUI_ID_MOVE_LEFT_BUTTON,
      GUI_ID_CHANGE_PLAYER_BUTTON,
      GUI_ID_APPLY_BUTTON,
      GUI_ID_CANCEL_BUTTON
    };

    OptionsState();
    virtual ~OptionsState();
    virtual void 				Init(is::GameEngine *engine);

   private:
    static const std::vector<irr::core::stringw>	NAME_OF_ACTIONS;
    Options						_options;
    OptionsEventReceiver				_optionsEventReceiver;

    void 					drawNameActions();
    OptionsEventReceiver::SOptionsContext	_optionsContext;
    std::map<Options::MOVES, irr::EKEY_CODE>	getPlayerConfig(irr::s8 player);
  };
}
