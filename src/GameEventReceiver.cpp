//
// Created by kyxo on 6/12/17.
//

#include <iostream>
#include <OptionsState.hpp>
#include "GameEventReceiver.hpp"
#include "PauseState.hpp"

is::GameEventReceiver::GameEventReceiver(CHANGE &change) : _change(change)
{
}

is::GameEventReceiver::~GameEventReceiver()
{

}

bool 		is::GameEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (_change != CHANGE::NONE)
    return (false);
  if(event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
    {
      switch (event.JoystickEvent.Axis[0])
	{
	  case (0):
	    {
	      _action = false;
	      _horAxe = 0;
	      _verAxe = 0;
	    }
	  break;
	  case (32767):
	    _horAxe = 1;
	  break;
	  case (-32767):
	    _horAxe = -1;
	  break;
	  default:
	    break;
	}
      switch (event.JoystickEvent.Axis[1])
	{
	  case (32767):
	    _verAxe = -1;
	  break;
	  case (-32767):
	    _verAxe = 1;
	  break;
	  default:
	    break;
	}
      if (event.JoystickEvent.IsButtonPressed(1))
	_action = true;
    }
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    this->_keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return (false);
}

void	is::GameEventReceiver::init()
{
  for (int i = 0; i < this->_keys.size(); i++)
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

irr::s16 		is::GameEventReceiver::isHorAxe(Button::GUI_ID_BOUTON id) const
{
  if (id == Button::GUI_ID_BOUTON::GUI_ID_PLAYER1_WINNER)
    return (_horAxe);
  else
    return (0);
}

irr::s16 		is::GameEventReceiver::isVerAxe(Button::GUI_ID_BOUTON id) const
{
  if (id == Button::GUI_ID_BOUTON::GUI_ID_PLAYER1_WINNER)
    return (_verAxe);
  else
    return (0);
}

void 			is::GameEventReceiver::setVerAxe(irr::s16 axe)
{
  _verAxe = axe;
}

void 			is::GameEventReceiver::setHorAxe(irr::s16 axe)
{
  _horAxe = axe;
}

bool 			is::GameEventReceiver::isActionOn(Button::GUI_ID_BOUTON id) const
{
  if (id == Button::GUI_ID_BOUTON::GUI_ID_PLAYER1_WINNER)
    return _action;
  else
    return false;
}