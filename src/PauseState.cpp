//
// greg
//

#include "PauseState.hpp"
#include "IndieStudioException.hpp"

namespace           is // tester le vite !
{
    PauseState::PauseState():
    MenuState(),

    _PauseEventReceiver()
    {
    }
    PauseState::~PauseState()
    {
    }

    void            PauseState::Init(GameEngine *engine)
    {
        this->_engine = engine;
        this->_sceneManager = this->_engine->getSceneManager();
        this->_driver = this->_engine->getDriver();
        this->_gui = this->_engine->getGuiEnv();
        this->_PauseEventReceiver.setEngine(this->_engine);
        this->_engine->getDevice()->setEventReceiver(&this->_PauseEventReceiver);
	this->_engine->getDevice()->getCursorControl()->setVisible(true);
        if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
            throw IndieStudioException("Not able to init the error message.");
        this->_buttons = {
 	        { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, 15, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_RESUME_BUTTON, L"", L"Launch the game" },
	        { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT * 2, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON, L"", L"Configure the game" },
	        { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT * 2, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT * 3, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON, L"", L"Return to the menu" },
        };
        this->initTexture();
        this->drawButtons();
    }
    void            PauseState::Resume()
    {
        this->_engine->getDevice()->setEventReceiver(&this->_PauseEventReceiver);
        this->drawButtons();
    }
}