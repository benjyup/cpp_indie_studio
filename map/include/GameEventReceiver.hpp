//
// Created by kyxo on 6/12/17.
//

#ifndef CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP


#pragma once

#include <vector>
#include <IGameState.hpp>
#include "irrlicht.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

namespace is
{
  class GameEventReceiver : public irr::IEventReceiver
  {
   public:
    GameEventReceiver();
    virtual ~GameEventReceiver();

    virtual bool 				OnEvent(const irr::SEvent& event);
    void					setDevice(irr::IrrlichtDevice *device);
    void					setEngine(GameEngine *engine);

    bool 					isKeyDown(irr::EKEY_CODE keyCode) const;

   private:
    irr::IrrlichtDevice					*_device;
    GameEngine						*_engine;
    std::vector<std::shared_ptr<IGameState>> 		_states;
    std::array<bool, irr::KEY_KEY_CODES_COUNT>		_keys;
  };
}


#endif //CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP
