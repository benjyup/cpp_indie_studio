//
// Created by vincent on 23/05/17.
//

#pragma once

#include <IrrlichtDevice.h>
#include "IEventReceiver.h"
#include "GameEngine.hpp"
#include "Button.hpp"

namespace is
{
  class OptionsEventReceiver : public irr::IEventReceiver
  {
   public:

    static const irr::core::stringw			PRESS_KEY;

    struct SOptionsContext
    {
      GameEngine 					*engine;
      irr::s8 						player;
      std::string  name;
      std::map<Options::MOVES, irr::EKEY_CODE>		player1ConfigTmp;
      std::map<Options::MOVES, irr::EKEY_CODE>		player2ConfigTmp;
      std::vector<is::Button> 				*buttons;
      irr::gui::IGUIStaticText				*errorMsg;
    };

    OptionsEventReceiver();
    virtual ~OptionsEventReceiver();

    virtual bool 		OnEvent(const irr::SEvent& event);
    void 			Init(SOptionsContext *optionsContext);

   private:
    SOptionsContext					*_optionsContext;
    bool 						_getKey;
    Button::GUI_ID_BOUTON 				_keyToChange;


    std::map<is::Options::MOVES, irr::EKEY_CODE> 	&_getPlayerConfig(irr::s8 player);
    void 						_refresh();
    void 						_guiEvent(const irr::SEvent &event);
    void 						_keyEvent(const irr::SEvent &event);
    void 						_initConfig(void);
  };
}
