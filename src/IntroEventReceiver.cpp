//
// greg
//

#include "IntroEventReceiver.hpp"
#include "MenuState.hpp"


namespace is
{
    IntroEventReceiver::IntroEventReceiver(): _device(NULL)
    {
    }
    IntroEventReceiver::~IntroEventReceiver()
    {
    }
    bool 		is::IntroEventReceiver::OnEvent(const irr::SEvent &event)
    {
    if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
        {
            irr::s32	buttonID = event.GUIEvent.Caller->getID();
            switch (buttonID)
            {
            default:
            this->_engine->ChangeState(new MenuState);
            break;
            }
        }
    else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE)
        this->_device->closeDevice();
    return (false);
    }

    void is::IntroEventReceiver::setDevice(irr::IrrlichtDevice *device)
    {
        this->_device = device;
    }

    void is::IntroEventReceiver::setEngine(GameEngine *engine)
    {
        this->_engine = engine;
        this->_device = engine->getDevice();
    }
}