//
// greg
//

#include "MenuState.hpp"
#include "Camera.hpp"
#include "Fire.hpp"
#include "map.hpp"
#include "PlanetSystem.hpp"

static std::vector<int>        mapi;

namespace is
{
  std::mutex					MenuState::DRAW_MUTEX;
  const irr::io::path		MenuState::WALLPAPER = "./gfx/menuWallpaper.png";
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

    if (!(this->_wallpaper = _engine->getDriver()->getTexture(WALLPAPER)))
      throw IndieStudioException();
    if (!(this->_errorMsg = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(100, 300, 300, 400))))
      throw IndieStudioException("Not able to init the error message.");
    if (_gui != NULL)
     this->_font = _gui->getFont("./gfx/font_space.bmp");
    this->_buttons = {
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, 15, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON, L"PLay", L"Launch the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT * 2, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON, L"Options", L"Configure the game" },
	    { engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT * 2, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, 15 + BUTTON_HEIGHT * 3, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit the game" },
     };

    mapi = _parserMap.getVector();
    _map = std::make_shared<is::map>(_driver, _sceneManager, mapi);
    _bombs = std::make_shared<is::BombsManager>(*(_map.get()), *_driver, *_sceneManager);
    _opt = _engine->getOptions();
    //_char[0] = std::make_shared<is::Character>(Character((_sceneManager->getMesh("./chef/tris.md2")), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(10 * SCALE + 7, 5, 10 * SCALE + 7)));
    //_map->addCollision(_char[0].get()->_mesh);
    //_char[1] = std::make_shared<is::Character>(Character((_sceneManager->getMesh("./chef/tris.md2")), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(3 * SCALE - SCALE / 2, 5, 2 * SCALE)));
    //_map->addCollision(_char[1].get()->_mesh);
    //_powManager = std::make_shared<is::PowerUpManager>(PowerUpManager(*_sceneManager, *_driver));
    //_powManager->newPow();
    //_receiver.init(_opt, _char);
    //_engine->getDevice()->setEventReceiver(&_receiver);
    //Vector3d	v(5 * SCALE + SCALE / 2 - SCALE, 0, 3 * SCALE + SCALE / 2 - SCALE);
    //_bomb = std::make_shared<is::BombsManager>(_map.get(), _driver, _sceneManager);
    //Vector3d	v(3, 3, 1);
    //_bomb->putBomb(v, 1);
    //_bombs->putBomb({6, 3, 0}, 10000);
    Camera	cam(_sceneManager, this->_driver, MENU, _engine);
    cam.setMenuMode();

    this->drawButtons();
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
    if (this->_wallpaper)
      this->_driver->draw2DImage(this->_wallpaper, irr::core::vector2d<irr::s32>(0, 0));

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
        col.set(50, 43, 50, 251);
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
