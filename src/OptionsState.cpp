//
// Created by vincent on 23/05/17.
//

#include "OptionsState.hpp"
#include "IndieStudioException.hpp"

is::OptionsState::OptionsState() :
	MenuState(),
	_optionsEventReceiver()
{
}

is::OptionsState::~OptionsState()
{
}

void is::OptionsState::Init(is::GameEngine *engine)
{

  this->_engine = engine;
  this->_sceneManager = this->_engine->getSceneManager();
  this->_driver = this->_engine->getDriver();
  this->_gui = this->_engine->getGuiEnv();
  this->_options = this->_engine->getOptions();
  auto windowSize = this->_engine->getWindowSize();
	 if (_gui != NULL)
      this->_font = _gui->getFont("./gfx/font_space.bmp");
	engine->getDevice()->setEventReceiver(&this->_optionsEventReceiver);

  if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
    throw IndieStudioException("Not able to init the error message.");

  //if (!(this->_wallpaper = _engine->getDriver()->getTexture(WALLPAPER)))
    //throw IndieStudioException();

  this->_optionsContext.engine = this->_engine;
  this->_optionsContext.player = 1;
  this->_optionsContext.buttons = &this->_buttons;
  this->_optionsContext.errorMsg = this->_errorMsg;
  this->_optionsEventReceiver.Init(&this->_optionsContext);
	this->_optionsContext.name = std::string("Player " + std::to_string(this->_optionsContext.player));
	
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
	  }
  };
	this->initTexture();
  this->drawButtons();
}

void is::OptionsState::Resume(void)
{
  this->_engine->getDevice()->setEventReceiver(&this->_optionsEventReceiver);
}