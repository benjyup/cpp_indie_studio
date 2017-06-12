//
// Created by kyxo on 6/12/17.
//

#include <iostream>
#include "GameEventReceiver.hpp"

is::GameEventReceiver::GameEventReceiver()
{
//  _char = Char;
  std::cout << "GameEventReceiver()" << std::endl;
}

void is::GameEventReceiver::init(Options const & opt, std::array<std::shared_ptr<Character>, 2> const &Char)
{
  _opt = opt;
  _p1_conf = _opt.getP1Config();
  _p2_conf = _opt.getP2Config();
  _char = Char;
}

is::GameEventReceiver::~GameEventReceiver()
{

}

bool 		is::GameEventReceiver::OnEvent(const irr::SEvent &event)
{
  for (auto const &i : _p1_conf)
    {
      if (i.second == event.KeyInput.Key)
	_char[0]->moove(i.first);
    }
 return (false);
}

void is::GameEventReceiver::setDevice(irr::IrrlichtDevice *device)
{
  this->_device = device;
}

void is::GameEventReceiver::setEngine(GameEngine *engine)
{
  this->_engine = engine;
  this->_device = engine->getDevice();
}
