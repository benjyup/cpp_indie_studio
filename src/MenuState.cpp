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
	  _wallpaper(NULL),
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

    //if (!(this->_wallpaper = _engine->getDriver()->getTexture(WALLPAPER)))
      //throw IndieStudioException();
    if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
      throw IndieStudioException("Not able to init the error message.");
    if (_gui != NULL)
     this->_font = _gui->getFont("./gfx/font_space.bmp");
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
        //char            a;
        //int             cpt;
        //std::string     button = "button.png";
        //std::string     tmp;

        //a = 97;
        //cpt = 16;
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
        this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER_BUTTON] = this->_driver->getTexture("./ButtonGFX/p1button.png");
        this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON] = this->_driver->getTexture("./ButtonGFX/playbutton.png");// manque
        this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON] = this->_driver->getTexture("./ButtonGFX/menubutton.png");
        this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_RESUME_BUTTON] = this->_driver->getTexture("./ButtonGFX/resumebutton.png");
        this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_WALLPAPER_BUTTON] = this->_driver->getTexture("./ButtonGFX/bomberman3dtitle.png");
        this->_pathButton[Button::GUI_ID_BOUTON::GUI_ID_PRESS_BUTTON] = this->_driver->getTexture("./ButtonGFX/pressakeybutton.png");
        //while (a <= 122)
        //{
          //tmp = a;
          //this->_pathButton[(Button::GUI_ID_BOUTON)((irr::s32)cpt)] = this->_driver->getTexture(tmp + button); 
          //a++;
          //cpt++;
        //}
     }
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
        button->setOverrideFont(this->_font);
        button->setImage(this->_pathButton[(Button::GUI_ID_BOUTON)button->getID()]);
        button->setScaleImage(true);
        button->draw();
      }
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
