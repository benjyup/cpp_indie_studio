//
// greg
//

#include "ScoreEnd.hpp"

namespace is
{
  ScoreEnd::ScoreEnd():
	  MenuState(),
	  _change(CHANGE::NONE),
	  _ScoreEndReceiver(_change)
  { }

  ScoreEnd::~ScoreEnd()
  {

  }

  void ScoreEnd::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_driver = engine->getDriver();
    this->_sceneManager = engine->getSceneManager();
    this->_engine->getDevice()->setEventReceiver(NULL);
    _engine->getDevice()->getCursorControl()->setVisible(true);
    this->_gui = engine->getGuiEnv();
    this->_ScoreEndReceiver.setEngine(this->_engine);
    this->_engine->getSound().setGameMusicWin();
    this->_buttons = {
	    {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 12, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON, L"", L"Return to the menu"},
	    {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON, L"", L"Play new game"},
	    {engine->getWindowSize().X / 2 - 200, engine->getWindowSize().Y / 2 - 400, engine->getWindowSize().X / 2 + 200, engine->getWindowSize().Y / 2 - 200, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_WINNER, L"", L"Print Winner"},
	    {engine->getWindowSize().X / 2 - 150, engine->getWindowSize().Y / 2 - 200, engine->getWindowSize().X / 2 + 150, engine->getWindowSize().Y / 2, (irr::s32)this->_engine->getWinner(), L"", L"Print Winner name"}
    };
    this->initTexture();
    this->drawButtons();
    this->_engine->getDevice()->setEventReceiver(&this->_ScoreEndReceiver);
  }

  void ScoreEnd::Resume()
  {
    _engine->getDevice()->getCursorControl()->setVisible(true);
    this->_engine->getDevice()->setEventReceiver(&this->_ScoreEndReceiver);
    this->drawButtons();
  }

  void is::ScoreEnd::HandleEvents(void)
  {
    if (_change == CHANGE::POP)
      _engine->PopState();
    else if (_change == CHANGE::GAME)
	_engine->ChangeState(new GameState);
  }
}