//
// greg
//

#include "MenuState.hpp"
#include "Camera.hpp"
#include "Fire.hpp"
#include "map.hpp"
#include "PlanetSystem.hpp"

namespace is
{
  std::mutex					MenuState::DRAW_MUTEX;
  const irr::io::path		MenuState::WALLPAPER = "./ButtonGFX/bomberman3dtitle.png";
  const irr::s32		MenuState::BUTTON_WIDTH = 250;
  const irr::s32		MenuState::BUTTON_HEIGHT = 75;
  
  MenuState::MenuState() :
	  _menuEventReceiver(),
	  _errorMsg(NULL),
    _parserMap("map01.txt")
  {
  }

  MenuState::~MenuState()
  {
  }

  void MenuState::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_sceneManager = this->_engine->getSceneManager();
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    this->_menuEventReceiver.setEngine(this->_engine);
    this->_engine->getDevice()->setEventReceiver(&this->_menuEventReceiver);

    if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
      throw IndieStudioException("Not able to init the error message.");
    this->_buttons = {
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 4 - 45, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 3 - 30, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON, L"", L"Launch the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 3 - 30, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 2 - 15, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON, L"", L"Configure the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT * 2 - 15, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - BUTTON_HEIGHT, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON, L"", L"Quit the game"},
      { engine->getWindowSize().X / 2 - 545 / 2, 30, engine->getWindowSize().X / 2 + 575 / 2, 375, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_WALLPAPER_BUTTON, L"", L"WALLPAPER"},
     };
    _mapi = _parserMap.getVector();
    _map = std::make_shared<is::map>(_driver, _sceneManager, _mapi);
    Camera	cam(_sceneManager, this->_driver, MENU, _engine);
    cam.setMenuMode();
    this->initTexture();
    this->drawButtons();
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
        this->initKeyTexture();
     }
  }
  void MenuState::initKeyTexture()
  {
    this->_pathKey[irr::KEY_KEY_A] = this->_driver->getTexture("./ButtonGFX/abutton.png");
    this->_pathKey[irr::KEY_KEY_B] = this->_driver->getTexture("./ButtonGFX/bbutton.png");
    this->_pathKey[irr::KEY_KEY_C] = this->_driver->getTexture("./ButtonGFX/cbutton.png");
    this->_pathKey[irr::KEY_KEY_D] = this->_driver->getTexture("./ButtonGFX/dbutton.png");
    this->_pathKey[irr::KEY_KEY_E] = this->_driver->getTexture("./ButtonGFX/ebutton.png");
    this->_pathKey[irr::KEY_KEY_F] = this->_driver->getTexture("./ButtonGFX/fbutton.png");
    this->_pathKey[irr::KEY_KEY_G] = this->_driver->getTexture("./ButtonGFX/gbutton.png");
    this->_pathKey[irr::KEY_KEY_H] = this->_driver->getTexture("./ButtonGFX/hbutton.png");
    this->_pathKey[irr::KEY_KEY_I] = this->_driver->getTexture("./ButtonGFX/ibutton.png");
    this->_pathKey[irr::KEY_KEY_J] = this->_driver->getTexture("./ButtonGFX/jbutton.png");
    this->_pathKey[irr::KEY_KEY_K] = this->_driver->getTexture("./ButtonGFX/kbutton.png");
    this->_pathKey[irr::KEY_KEY_L] = this->_driver->getTexture("./ButtonGFX/lbutton.png");
    this->_pathKey[irr::KEY_KEY_M] = this->_driver->getTexture("./ButtonGFX/mbutton.png");
    this->_pathKey[irr::KEY_KEY_N] = this->_driver->getTexture("./ButtonGFX/nbutton.png");
    this->_pathKey[irr::KEY_KEY_O] = this->_driver->getTexture("./ButtonGFX/obutton.png");
    this->_pathKey[irr::KEY_KEY_P] = this->_driver->getTexture("./ButtonGFX/pbutton.png");
    this->_pathKey[irr::KEY_KEY_Q] = this->_driver->getTexture("./ButtonGFX/qbutton.png");
    this->_pathKey[irr::KEY_KEY_R] = this->_driver->getTexture("./ButtonGFX/rbutton.png");
    this->_pathKey[irr::KEY_KEY_S] = this->_driver->getTexture("./ButtonGFX/sbutton.png");
    this->_pathKey[irr::KEY_KEY_T] = this->_driver->getTexture("./ButtonGFX/tbutton.png");
    this->_pathKey[irr::KEY_KEY_U] = this->_driver->getTexture("./ButtonGFX/ubutton.png");
    this->_pathKey[irr::KEY_KEY_V] = this->_driver->getTexture("./ButtonGFX/vbutton.png");
    this->_pathKey[irr::KEY_KEY_W] = this->_driver->getTexture("./ButtonGFX/wbutton.png");
    this->_pathKey[irr::KEY_KEY_X] = this->_driver->getTexture("./ButtonGFX/xbutton.png");
    this->_pathKey[irr::KEY_KEY_Y] = this->_driver->getTexture("./ButtonGFX/ybutton.png");
    this->_pathKey[irr::KEY_KEY_Z] = this->_driver->getTexture("./ButtonGFX/zbutton.png");

    this->_pathKey[irr::KEY_LEFT] = this->_driver->getTexture("./ButtonGFX/leftarrowbutton.png");
    this->_pathKey[irr::KEY_RIGHT] = this->_driver->getTexture("./ButtonGFX/rightarrowbutton.png");
    this->_pathKey[irr::KEY_UP] = this->_driver->getTexture("./ButtonGFX/uparrowbutton.png");
    this->_pathKey[irr::KEY_DOWN] = this->_driver->getTexture("./ButtonGFX/downarrowbutton.png");
    this->_pathKey[irr::KEY_SPACE] = this->_driver->getTexture("./ButtonGFX/spacebarbutton.png");
  }
  void MenuState::Cleanup(void)
  {
  }

  void MenuState::Pause(void)
  {
  }

  void MenuState::Resume(void)
  {
    this->_engine->getDevice()->setEventReceiver(&this->_menuEventReceiver);
    this->drawButtons();
  }

  void MenuState::HandleEvents(void)
  {
  }

  void MenuState::Update(void)
  {
  }

  void MenuState::Draw(void)
  {
    this->_driver->beginScene();
    {
      std::unique_lock<std::mutex> lock(DRAW_MUTEX);
      _sceneManager->drawAll();
    }
    for (auto &text : this->_text)
    {
      text->draw();
    }
    for (auto &button : this->_buttons)
      {
        if (button.getPress() == 1)
          button->setImage(this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_PRESS_BUTTON]);
        else
        {
          switch ((Button::GUI_ID_BOUTON)button->getID())
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

