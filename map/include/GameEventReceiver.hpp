//
// Created by kyxo on 6/12/17.
//

#ifndef CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP


#pragma once

#include <vector>
#include <IGameState.hpp>
#include <Character.hpp>
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
    void 	init(Options const & opt, std::array<std::shared_ptr<Character>, 2> const &Char);

   private:
    irr::IrrlichtDevice					*_device;
    GameEngine						*_engine;
    std::vector<std::shared_ptr<IGameState>> 		_states;
    Options						_opt;
    std::map<Options::MOVES, irr::EKEY_CODE>	_p1_conf;
    std::map<Options::MOVES, irr::EKEY_CODE>	_p2_conf;
    std::array<std::shared_ptr<Character>, 2>		_char;
  };
}


#endif //CPP_INDIE_STUDIO_GAMEEVENTRECEIVER_HPP
