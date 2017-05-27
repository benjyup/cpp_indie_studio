//
// Created by vincent on 23/05/17.
//

#include "OptionsState.hpp"
#include "IndieStudioException.hpp"


const std::vector<irr::core::stringw>		is::OptionsState::NAME_OF_ACTIONS = {
	"Put a bomb",
	"Move forward",
	"Move backward",
	"Move right",
	"Move left",
};

is::OptionsState::OptionsState() :
	MenuState(),
	_optionsEventReceiver()
{

}

is::OptionsState::~OptionsState()
{
  std::cout << "DESTRUCTEUR DE OPTION STATE" << std::endl;
}

void is::OptionsState::Init(is::GameEngine *engine)
{
  this->_engine = engine;
  this->_sceneManager = this->_engine->getSceneManager();
  this->_driver = this->_engine->getDriver();
  this->_gui = this->_engine->getGuiEnv();
  this->_options = this->_engine->getOptions();
  auto windowSize = this->_engine->getWindowSize();
  engine->getDevice()->setEventReceiver(&this->_optionsEventReceiver);

  if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
    throw IndieStudioException("Not able to init the error message.");

  if (!(this->_wallpaper = _engine->getDriver()->getTexture(WALLPAPER)))
    throw IndieStudioException();

  this->_optionsContext.engine = this->_engine;
  this->_optionsContext.player = 1;
  this->_optionsContext.buttons = &this->_buttons;
  this->_optionsContext.errorMsg = this->_errorMsg;
  this->_optionsEventReceiver.Init(&this->_optionsContext);

  this->_buttons = {
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2,
		  15,
		  windowSize.X / 2 + BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_ACTION_BUTTON,
		  this->_options.keyToString<irr::core::stringw>(getPlayerConfig(this->_optionsContext.player).at(Options::MOVES::MOVE_ACTION)).c_str()//
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT,
		  windowSize.X / 2 + BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 2,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_FORWARD_BUTTON,
		  this->_options.keyToString<irr::core::stringw>(getPlayerConfig(this->_optionsContext.player).at(Options::MOVES::MOVE_UP)).c_str()
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 2,
		  windowSize.X / 2 + BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 3,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_BACKWARD_BUTTON,
		  this->_options.keyToString<irr::core::stringw>(getPlayerConfig(this->_optionsContext.player).at(Options::MOVES::MOVE_DOWN)).c_str()
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 3,
		  windowSize.X / 2 + BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 4,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_RIGHT_BUTTON,
		  this->_options.keyToString<irr::core::stringw>(getPlayerConfig(this->_optionsContext.player).at(Options::MOVES::MOVE_RIGHT)).c_str()
	  },
	  {
		  windowSize.X / 2 - MenuState::BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 4,
		  windowSize.X / 2 + BUTTON_WIDTH / 2,
		  15 + BUTTON_HEIGHT * 5,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_MOVE_LEFT_BUTTON,
		  this->_options.keyToString<irr::core::stringw>(getPlayerConfig(this->_optionsContext.player).at(Options::MOVES::MOVE_LEFT)).c_str()
	  },
	  {
		  windowSize.X - 20 - MenuState::BUTTON_WIDTH,
		  windowSize.Y - BUTTON_HEIGHT - 20,
		  windowSize.X - 20,
		  windowSize.Y - 20,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_APPLY_BUTTON,
		  "Apply"
	  },
	  {
		  windowSize.X - 20 - MenuState::BUTTON_WIDTH * 2,
		  windowSize.Y - BUTTON_HEIGHT - 20,
		  windowSize.X - 30 - MenuState::BUTTON_WIDTH,
		  windowSize.Y - 20,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_CANCEL_BUTTON,
		  "Cancel"
	  },
	  {
		  20,
		  20,
		  20 + BUTTON_WIDTH,
		  20 + BUTTON_HEIGHT,
		  (irr::s32) Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER_BUTTON,
		  "Player 1"
	  }
  };
  this->drawButtons();
  this->drawNameActions();
}

void is::OptionsState::Resume(void)
{
  this->_engine->getDevice()->setEventReceiver(&this->_optionsEventReceiver);
}

void 			is::OptionsState::drawNameActions()
{
  for (std::size_t i = 0 ; i < 5 ; i += 1)
    {
      this->_text.push_back(this->_gui->addStaticText(NAME_OF_ACTIONS.at(i).c_str(),
						      {this->_buttons[i].getX() - 100, this->_buttons[i].getY(),this->_buttons[i].getX() + 20, this->_buttons[i].getY() + 20}));
    }
}

std::map<is::Options::MOVES, irr::EKEY_CODE> is::OptionsState::getPlayerConfig(irr::s8 player)
{
  if (player == 1)
    return (this->_options.getP1Config());
  else
    return (this->_options.getP2Config());
}
