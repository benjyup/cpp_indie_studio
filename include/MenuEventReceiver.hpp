//
// Created by vincent on 23/05/17.
//

#pragma once

#include <vector>
#include "irrlicht.h"
#include "GameEngine.hpp"
#include "GameState.hpp"


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

namespace is
{
  class MenuEventReceiver : public irr::IEventReceiver
  {
   public:
    MenuEventReceiver(CHANGE &change, std::vector<is::Button> &_buttons);

    virtual ~MenuEventReceiver();

    virtual bool 				OnEvent(const irr::SEvent& event);
    void					setDevice(irr::IrrlichtDevice *device);
    void					setEngine(GameEngine *engine);

   private:
    irr::IrrlichtDevice				*_device;
    GameEngine					      *_engine;
    std::vector<std::shared_ptr<IGameState>> 	_states;
    CHANGE 				            &_change;
    std::vector<is::Button> 	&_buttons;
  };

}
