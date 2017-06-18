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
            {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 12, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON, L"", L"Return to the menu"},
            {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON, L"", L"Play new game"},
            {engine->getWindowSize().X / 2 - 200, engine->getWindowSize().Y / 2 - 400, engine->getWindowSize().X / 2 + 200, engine->getWindowSize().Y / 2 - 200, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_WINNER, L"", L"Print Winner"},
            {engine->getWindowSize().X / 2 - 150, engine->getWindowSize().Y / 2 - 200, engine->getWindowSize().X / 2 + 150, engine->getWindowSize().Y / 2, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER1_BUTTON, L"", L"Print Winner name"}
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