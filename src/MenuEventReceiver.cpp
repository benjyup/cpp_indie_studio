//
// Created by vincent on 23/05/17.
//

#include "MenuEventReceiver.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "OptionsState.hpp"

is::MenuEventReceiver::MenuEventReceiver() : _device(NULL)
{
  std::cout << "MenuEventReceiver()" << std::endl;
}

is::MenuEventReceiver::~MenuEventReceiver()
{

}

bool 		is::MenuEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
    {
      irr::s32	buttonID = event.GUIEvent.Caller->getID();
      switch (buttonID)
	{
	  case ((irr::s32)MenuState::GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON):
	    this->_engine->ChangeState(new GameState);
	  break;
	  case ((irr::s32)MenuState::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON):
	    this->_engine->ChangeState(new OptionsState);
	  break;
	  case ((irr::s32)MenuState::GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON):
	      this->_device->closeDevice();
	  break;
	  default:
	    std::cout << "AUCUN" << std::endl;
	}
    }
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
