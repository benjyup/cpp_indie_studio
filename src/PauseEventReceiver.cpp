//
// greg
//

#include "PauseEventReceiver.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "OptionsState.hpp"
#include "ScoreEnd.hpp"

is::PauseEventReceiver::PauseEventReceiver(CHANGE &change) : _change(change), _device(NULL)
{
}

is::PauseEventReceiver::~PauseEventReceiver()
{
}

bool 		is::PauseEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (_change == CHANGE::NONE && event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
    {
      irr::s32	buttonID = event.GUIEvent.Caller->getID();
      switch (buttonID)
	{
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_RESUME_BUTTON):
	    _change = CHANGE::POP;
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON):
	      _change = CHANGE::OPTION;
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_SAVE_BUTTON):
				_change = CHANGE::POP2;
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON):
	    {
	      _change = CHANGE::POP2;
	      _engine->getSound().setMenuMusic();
	    }
	  break;
	  default:
	    break;
	}
    }
//  else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE)
//      this->_device->closeDevice();
  return (false);
}

void is::PauseEventReceiver::setDevice(irr::IrrlichtDevice *device)
{
  this->_device = device;
}

void is::PauseEventReceiver::setEngine(GameEngine *engine)
{
  this->_engine = engine;
  this->_device = engine->getDevice();
}
