//
// Created by kyxo on 6/12/17.
//

#include <iostream>
#include <OptionsState.hpp>
#include "GameEventReceiver.hpp"
#include "PauseState.hpp"

is::GameEventReceiver::GameEventReceiver()
{
//  _char = Char;
  std::cerr << "GameEventReceiver()" << std::endl;
}

is::GameEventReceiver::~GameEventReceiver()
{

}

bool 		is::GameEventReceiver::OnEvent(const irr::SEvent &event)
{
/*
  for (auto const &i : _p1_conf)
    {
      if (i.second == event.KeyInput.Key)
	_char[0]->moove(i.first);
    }
*/
  this->_keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return (false);
}

void	is::GameEventReceiver::init()
{
  for (int i = 0 ; i < this->_keys.size() ; i++)
    this->_keys[i] = false;
}

void is::GameEventReceiver::setDevice(irr::IrrlichtDevice *device)
{
  this->_device = device;
  for (int i = 0 ; i < this->_keys.size() ; i++)
    this->_keys[i] = false;
}

void is::GameEventReceiver::setEngine(GameEngine *engine)
{
  this->_engine = engine;
  this->_device = engine->getDevice();
}

bool 			is::GameEventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->_keys[keyCode]);
}
