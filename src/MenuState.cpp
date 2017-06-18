//
// greg
//

#include <OptionsState.hpp>
#include <ChoosePlayerState.hpp>
#include "MenuState.hpp"
#include "Camera.hpp"
#include "Fire.hpp"
#include "map.hpp"
#include "PlanetSystem.hpp"
#include "ScoreEnd.hpp"

namespace is
{
  const irr::io::path		MenuState::WALLPAPER = "./ButtonGFX/bomberman3dtitle.png";
  const irr::s32		MenuState::BUTTON_WIDTH = 250;
  const irr::s32		MenuState::BUTTON_HEIGHT = 75;

  MenuState::MenuState() : _change(CHANGE::NONE), _menuEventReceiver(_change, _buttons), _errorMsg(NULL), _parserMap("map01.txt")
  {
    std::cerr << "Menu Event()" << std::endl;
  }

  MenuState::~MenuState()
  {
  }

  void MenuState::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_sceneManager = this->_engine->getSceneManager();
//    _sceneManager->clear();
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    this->_engine->getDevice()->setEventReceiver(NULL);
    this->_menuEventReceiver.setEngine(this->_engine);
    this->_engine->getDevice()->getCursorControl()->setVisible(true);
    this->_engine->getSound().setMenuMusic();
    if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
      throw IndieStudioException("Not able to init the error message.");
    this->_buttons = {
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 4 - 60, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 3 - 45, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON, L"", L"Launch the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 3 - 45, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 2 - 30, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_LOAD_BUTTON, L"", L"Configure the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 2 - 30, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT - 15, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON, L"", L"Configure the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT - 15, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON, L"", L"Quit the game"},
	    { engine->getWindowSize().X / 2 - 545 / 2, 30, engine->getWindowSize().X / 2 + 575 / 2, 375, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_WALLPAPER_BUTTON, L"", L"WALLPAPER"},
    };
    _mapi = _parserMap.getVector();
    _map = std::make_shared<is::map>(_driver, _sceneManager, _mapi);
    Camera	cam(_sceneManager, this->_driver, MENU, _engine);
    cam.setMenuMode();
    this->initTexture();
    this->drawButtons();
    this->_engine->getDevice()->setEventReceiver(&this->_menuEventReceiver);
  }

  void MenuState::initTexture()
  {
    if (this->_driver)
      {
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON] = this->_driver->getTexture("./ButtonGFX/playbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON] = this->_driver->getTexture("./ButtonGFX/optionsbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON] = this->_driver->getTexture("./ButtonGFX/quitbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_APPLY_BUTTON] = this->_driver->getTexture("./ButtonGFX/applybutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_CANCEL_BUTTON] = this->_driver->getTexture("./ButtonGFX/cancelbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MOVE_ACTION_BUTTON] = this->_driver->getTexture("./ButtonGFX/putabombbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MOVE_FORWARD_BUTTON] = this->_driver->getTexture("./ButtonGFX/moveforwardbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MOVE_BACKWARD_BUTTON] = this->_driver->getTexture("./ButtonGFX/movebackwardbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MOVE_RIGHT_BUTTON] = this->_driver->getTexture("./ButtonGFX/moverightbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MOVE_LEFT_BUTTON] = this->_driver->getTexture("./ButtonGFX/moveleftbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_ACTION_BUTTON] = this->_driver->getTexture("./ButtonGFX/putabombbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_FORWARD_BUTTON] = this->_driver->getTexture("./ButtonGFX/moveforwardbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_BACKWARD_BUTTON] = this->_driver->getTexture("./ButtonGFX/movebackwardbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_RIGHT_BUTTON] = this->_driver->getTexture("./ButtonGFX/moverightbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_LEFT_BUTTON] = this->_driver->getTexture("./ButtonGFX/moveleftbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER1_BUTTON] = this->_driver->getTexture("./ButtonGFX/p1button.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER2_BUTTON] = this->_driver->getTexture("./ButtonGFX/p2button.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON] = this->_driver->getTexture("./ButtonGFX/replaybutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON] = this->_driver->getTexture("./ButtonGFX/menubutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_RESUME_BUTTON] = this->_driver->getTexture("./ButtonGFX/resumebutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_WALLPAPER_BUTTON] = this->_driver->getTexture("./ButtonGFX/bomberman3dtitle.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_PRESS_BUTTON] = this->_driver->getTexture("./ButtonGFX/pressakeybutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_WINNER] = this->_driver->getTexture("./ButtonGFX/thewinnerisbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_LOAD_BUTTON] = this->_driver->getTexture("./ButtonGFX/loadbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_SAVE_BUTTON] = this->_driver->getTexture("./ButtonGFX/savebutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_SOUND_ON_BUTTON] = this->_driver->getTexture("./ButtonGFX/soundonbutton.png");
	this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_SOUND_OFF_BUTTON] = this->_driver->getTexture("./ButtonGFX/soundoffbutton.png");

	this->initKeyTexture();
      }
  }

  void MenuState::initKeyTexture()
  {
    int               i = 0;
    std::string       doss = "./ButtonGFX/";
    std::string       buttonpng = "button.png";
    std::string       tmp;

    while (i != irr::KEY_KEY_CODES_COUNT)
      {
	irr::core::string<char> s(_options.keyToString<irr::core::stringw>((irr::EKEY_CODE)i));
	std::string  key(s.c_str());
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	this->removeSpace(key);
	if (key.find("num") != std::string::npos)
	  this->removeNum(key);
	tmp = doss + key + buttonpng;
	if ((this->_pathKey[(irr::EKEY_CODE)i] = this->_driver->getTexture(irr::io::path(tmp.c_str()))) == NULL)
	  this->_pathKey[(irr::EKEY_CODE)i] = this->_driver->getTexture(irr::io::path("./ButtonGFX/voidbutton.png"));
	i++;
      }
  }
  void MenuState::removeSpace(std::string &str)
  {
    int cpt = 0;

    while (str[cpt] != '\0')
      {
	if (str[cpt] == ' ')
	  str.erase(cpt, 1);
	cpt++;
      }
  }
  void MenuState::removeNum(std::string &str)
  {
    int cpt = str.find("num");

    while (str[cpt] != 'm')
      {
	str.erase(cpt, 1);
      }
    str.erase(cpt, 1);
  }
  void MenuState::Cleanup(void)
  {
  }

  void MenuState::Pause(void)
  {
    _change = CHANGE::NONE;
  }

  void MenuState::Resume(void)
  {
    _change = CHANGE::NONE;
    this->drawButtons();
    this->_engine->getDevice()->getCursorControl()->setVisible(true);
    this->_engine->getDevice()->setEventReceiver(&this->_menuEventReceiver);
    _engine->setSceneManager(_sceneManager);
  }

  void MenuState::HandleEvents(void)
  {
    if (_change == CHANGE::GAME)
      _engine->PushState(new ChoosePlayerState);
    else if (_change == CHANGE::OPTION)
	_engine->PushState(new OptionsState);
      else if (_change == CHANGE::QUIT)
	  _engine->Quit();
  }

  void MenuState::Update(void)
  {
  }

  void MenuState::Draw(void)
  {
    this->_driver->beginScene();
    _sceneManager->drawAll();
    for (auto &text : this->_text)
      {
	text->draw();
      }
    for (auto &button : this->_buttons)
      {
	Button::GUI_ID_BOUTON but = (Button::GUI_ID_BOUTON)button->getID();

	if (button.getPress() == 1)
	  button->setImage(this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_PRESS_BUTTON]);
	else
	  {
	    switch (but)
	      {
		case  Button::GUI_ID_BOUTON::GUI_ID_MOVE_ACTION_BUTTON:
		  if (this->_optionsContext.player == 1)
		    button->setImage(this->_pathKey[this->_optionsContext.player1ConfigTmp[Options::MOVES::MOVE_ACTION]]);
		  else
		    button->setImage(this->_pathKey[this->_optionsContext.player2ConfigTmp[Options::MOVES::MOVE_ACTION]]);
		break;
		case  Button::GUI_ID_BOUTON::GUI_ID_MOVE_FORWARD_BUTTON:
		  if (this->_optionsContext.player == 1)
		    button->setImage(this->_pathKey[this->_optionsContext.player1ConfigTmp[Options::MOVES::MOVE_UP]]);
		  else
		    button->setImage(this->_pathKey[this->_optionsContext.player2ConfigTmp[Options::MOVES::MOVE_UP]]);
		break;
		case  Button::GUI_ID_BOUTON::GUI_ID_MOVE_BACKWARD_BUTTON:
		  if (this->_optionsContext.player == 1)
		    button->setImage(this->_pathKey[this->_optionsContext.player1ConfigTmp[Options::MOVES::MOVE_DOWN]]);
		  else
		    button->setImage(this->_pathKey[this->_optionsContext.player2ConfigTmp[Options::MOVES::MOVE_DOWN]]);
		break;
		case  Button::GUI_ID_BOUTON::GUI_ID_MOVE_RIGHT_BUTTON:
		  if (this->_optionsContext.player == 1)
		    button->setImage(this->_pathKey[this->_optionsContext.player1ConfigTmp[Options::MOVES::MOVE_RIGHT]]);
		  else
		    button->setImage(this->_pathKey[this->_optionsContext.player2ConfigTmp[Options::MOVES::MOVE_RIGHT]]);
		break;
		case  Button::GUI_ID_BOUTON::GUI_ID_MOVE_LEFT_BUTTON:
		  if (this->_optionsContext.player == 1)
		    button->setImage(this->_pathKey[this->_optionsContext.player1ConfigTmp[Options::MOVES::MOVE_LEFT]]);
		  else
		    button->setImage(this->_pathKey[this->_optionsContext.player2ConfigTmp[Options::MOVES::MOVE_LEFT]]);
		break;
		default:
		  button->setImage(this->_pathButton[(Button::GUI_ID_BOUTON)button->getID()]);
		break;
	      }
	  }
	button->setScaleImage(true);
	button->draw();
      }
    if (_errorMsg != NULL)
      this->_errorMsg->draw();
    this->_driver->endScene();
  }

  void MenuState::ChangeState(GameEngine *engine,
			      IGameState *state)
  {
    this->_engine->ChangeState(state);
  }
}

void is::MenuState::drawButtons()
{
  for (auto &it : this->_buttons)
    {
      it.set(this->_gui->addButton({it.getX(), it.getY(), it.getX2(), it.getY2()},
				   0,
				   it.getId(),
				   it.getText().c_str(),
				   it.getHint().c_str()));
      it->setUseAlphaChannel(true);
    }
  for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT; ++i)
    {
      if (i != irr::gui::EGDC_BUTTON_TEXT)
      {
        irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        col.set(0, 43, 50, 251);
        _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
      }
      else
      {
        irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        col.set(255, 255, 255, 255);
        _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);      
      }
    }
}

std::map<is::Options::MOVES, irr::EKEY_CODE> is::MenuState::getPlayerConfig(irr::s8 player)
{
  if (player == 1)
    return (this->_options.getP1Config());
  else
    return (this->_options.getP2Config());
}

