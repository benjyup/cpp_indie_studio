//
// greg
//

#include "ScoreEndEventReceiver.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"

namespace is
{
    ScoreEndEventReceiver::ScoreEndEventReceiver(): _device(NULL)
    {
    }
    ScoreEndEventReceiver::~ScoreEndEventReceiver()
    {
    }
    bool                    ScoreEndEventReceiver::OnEvent(const irr::SEvent &event)
    {
        if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
        {
            irr::s32    idButton = event.GUIEvent.Caller->getID();
            switch (idButton)
            {
            case  ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON):
	      {
		this->_engine->getSound().setMenuMusic();
		this->_engine->PopState();
	      }
                break;
            case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON):
	      {
		this->_engine->getSound().setGameMusic();
		this->_engine->ChangeState(new GameState);
	      }
		break;
            default:
                break;
            }
        }
        else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE)
          this->_device->closeDevice();
        return (false);
    }
    void                    ScoreEndEventReceiver::setDevice(irr::IrrlichtDevice *device)
    {
        this->_device = device;
    }
    void                    ScoreEndEventReceiver::setEngine(GameEngine *engine)
    {
        this->_engine = engine;
        this->_device = engine->getDevice();
    }
}