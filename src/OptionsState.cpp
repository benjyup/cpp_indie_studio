//
// Created by vincent on 23/05/17.
//

#include "OptionsState.hpp"
#include "IndieStudioException.hpp"

is::OptionsState::OptionsState() :
	MenuState(),
	_change(CHANGE::NONE),
	_optionsEventReceiver(_change)
{
}

is::OptionsState::~OptionsState()
{
}

void is::OptionsState::Init(is::GameEngine *engine)
{
  this->_engine = engine;
  engine->getDevice()->setEventReceiver(NULL);
  this->_sceneManager = this->_engine->getSceneManager();
  this->_driver = this->_engine->getDriver();
  this->_gui = this->_engine->getGuiEnv();
  this->_options = this->_engine->getOptions();
  this->_engine->getDevice()->getCursorControl()->setVisible(true);
  auto windowSize = this->_engine->getWindowSize();

  if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
    throw IndieStudioException("Not able to init the error message.");
	this->_optionsContext.engine = this->_engine;
  this->_optionsContext.player = 1;
  this->_optionsContext.buttons = &this->_buttons;
  this->_optionsContext.errorMsg = this->_errorMsg;
  this->_optionsEventReceiver.Init(&this->_optionsContext);
	this->_optionsContext.name = std::string("Player " + std::to_string(this->_optionsContext.player));
	irr::s32 sound;
	if (_engine->getSound().get_soundEngine()->getSoundVolume() == 0)
		sound = (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_SOUND_OFF_BUTTON;
	else
		sound = (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_SOUND_ON_BUTTON;
	this->_buttons = {
		//---------------DROITE
		  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 + 130,
		  15,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_ACTION_BUTTON,
			""
		  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 2,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_FORWARD_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 2,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 3,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_BACKWARD_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 3,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 4,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_RIGHT_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 4,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 + 130,
		  15 + BUTTON_HEIGHT * 5,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_LEFT_BUTTON,
			""
	  },
		//------------FIN
		//------------GAUCHE
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 - 130,
		  15,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_ACTION_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 2,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_FORWARD_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 2,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 3,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_BACKWARD_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 3,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 4,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_RIGHT_BUTTON,
			""
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 4,
		  windowSize.X / 2 + BUTTON_WIDTH / 2 - 130,
		  15 + BUTTON_HEIGHT * 5,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_LEFT_BUTTON,
			""
	  },
		//-------------FIN
		{
		  windowSize.X - 20 - MenuState::BUTTON_WIDTH,
		  windowSize.Y - BUTTON_HEIGHT - 20,
		  windowSize.X - 20,
		  windowSize.Y - 20,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_APPLY_BUTTON,
			""
	  },
	  {
		  windowSize.X - 20 - MenuState::BUTTON_WIDTH * 2,
		  windowSize.Y - BUTTON_HEIGHT - 20,
		  windowSize.X - 30 - MenuState::BUTTON_WIDTH,
		  windowSize.Y - 20,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_CANCEL_BUTTON,
		  ""
	  },
	  {
		  20,
		  20,
		  20 + BUTTON_WIDTH,
		  20 + BUTTON_HEIGHT,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER1_BUTTON,
			""
	  },
	  {
		  20,
		  windowSize.Y - BUTTON_HEIGHT - 20,
			20 + BUTTON_WIDTH,
		  windowSize.Y - 20,
		  sound,
			""
	  }
  };

  this->initTexture();
  this->drawButtons();
  engine->getDevice()->setEventReceiver(&this->_optionsEventReceiver);
}

void is::OptionsState::Resume(void)
{
  this->_engine->getDevice()->setEventReceiver(&this->_optionsEventReceiver);
  this->_engine->getDevice()->getCursorControl()->setVisible(true);
  this->drawButtons();
}

void is::OptionsState::HandleEvents(void)
{
  if (_change == CHANGE::POP)
    _engine->PopState();
}
