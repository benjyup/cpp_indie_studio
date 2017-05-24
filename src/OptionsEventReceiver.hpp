//
// Created by vincent on 23/05/17.
//

#pragma once

#include <IrrlichtDevice.h>
#include "IEventReceiver.h"
#include "GameEngine.hpp"

namespace is
{
  class OptionsEventReceiver : public irr::IEventReceiver
  {
   public:
    struct SOptionsContext
    {
      GameEngine 					*engine;
      irr::s8 						player;
    };

    OptionsEventReceiver();
    virtual ~OptionsEventReceiver();

    virtual bool 		OnEvent(const irr::SEvent& event);
    void 			Init(SOptionsContext *optionsContext);

   private:
    SOptionsContext		*_optionsContext;
  };
}
