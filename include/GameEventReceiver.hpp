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
    GameEventReceiver(CHANGE &);
    virtual ~GameEventReceiver();

    void					init();
    virtual bool 				OnEvent(const irr::SEvent& event);
    void					setDevice(irr::IrrlichtDevice *device);
    void					setEngine(GameEngine *engine);

    bool 					isKeyDown(irr::EKEY_CODE keyCode) const;
    irr::s16 					isHorAxe(Button::GUI_ID_BOUTON id) const;
    irr::s16 					isVerAxe(Button::GUI_ID_BOUTON id) const;
    void					setVerAxe(irr::s16 axe);
    void					setHorAxe(irr::s16 axe);
    bool 					isActionOn(Button::GUI_ID_BOUTON id) const;

   private:
    CHANGE						_change;
    irr::IrrlichtDevice					*_device;
    GameEngine						*_engine;
    std::vector<std::shared_ptr<IGameState>> 		_states;
    std::array<bool, irr::KEY_KEY_CODES_COUNT>		_keys;
    //std::array<bool, irr::SJoystickInfo::Axes>		_joys;
    irr::SEvent::SJoystickEvent				_JoystickState;
    irr::s16 						_horAxe;
    irr::s16 						_verAxe;
    bool						_action;
  };
}


#endif //CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP
