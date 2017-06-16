//
// greg
//

#include "ScoreEnd.hpp"

namespace is
{ 
    ScoreEnd::ScoreEnd():
    MenuState(),
    _ScoreEndReceiver()
	{

    }
    ScoreEnd::~ScoreEnd()
    {

    }
    void ScoreEnd::Init(GameEngine *engine)
    {
        this->_engine = engine;
        this->_driver = engine->getDriver();
        this->_sceneManager = engine->getSceneManager();
        this->_gui = engine->getGuiEnv();
        this->_ScoreEndReceiver.setEngine(this->_engine);
        this->_engine->getDevice()->setEventReceiver(&this->_ScoreEndReceiver);
        this->_buttons = {
            {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON, L"", L"Return to the menu"},
            {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT - 15, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON, L"", L"Play new game"}
        };
        this->initTexture();
        this->drawButtons();
    }
    void ScoreEnd::Resume()
    {
        this->_engine->getDevice()->setEventReceiver(&this->_ScoreEndReceiver);
        this->drawButtons();
    }
}