//
// Created by vincent on 23/05/17.
//

#include <ChoosePlayerState.hpp>
#include "MenuEventReceiver.hpp"
#include "OptionsState.hpp"

is::MenuEventReceiver::MenuEventReceiver(CHANGE &change, std::vector<is::Button> &buttons) : _device(NULL), _change(change), _buttons(buttons)
{
  std::cout << "MenuEventReceiver()" << std::endl;
}

is::MenuEventReceiver::~MenuEventReceiver()
{

}

bool 		is::MenuEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (_change == CHANGE::NONE && event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
    {
      irr::s32 buttonID = event.GUIEvent.Caller->getID();
      switch (buttonID)
	{
	  case ((irr::s32) Button::GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON):
	    _change = CHANGE::GAME;
	  break;
	  case ((irr::s32) Button::GUI_ID_BOUTON::GUI_ID_LOAD_BUTTON):
	    _change = CHANGE::GAME; // change pour load le game
	  break;
	  case ((irr::s32) Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON):
	    _change = CHANGE::OPTION;
	  break;
	  case ((irr::s32) Button::GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON):
	    _change = CHANGE::QUIT;
	  break;
	  default:
	    break;
	}
    }
  else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE)
      this->_device->closeDevice();
  return (false);
}

void is::MenuEventReceiver::setDevice(irr::IrrlichtDevice *device)
{
  this->_device = device;
}

void is::MenuEventReceiver::setEngine(GameEngine *engine)
{
  this->_engine = engine;
  this->_device = engine->getDevice();
}