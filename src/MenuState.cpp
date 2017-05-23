//
// greg
//

#include "MenuState.hpp"
#include "IndieStudioException.hpp"

#include "Button.hpp"

namespace is
{

  const irr::io::path		MenuState::WALLPAPER = "./menuWallpaper.jpg";
  const irr::s32		MenuState::BUTTON_WIDTH = 250;
  const irr::s32		MenuState::BUTTON_HEIGHT = 75;

  std::vector<is::Button> MenuState::BUTTONS = {
	  { 15, 15, 15 + BUTTON_WIDTH, 15 + BUTTON_HEIGHT, (irr::s32)GUI_ID_BOUTON::GUI_ID_PLAY_BUTTON, L"PLay", L"Launch the game" },
	  { 15, 15 + BUTTON_HEIGHT, 15 + BUTTON_WIDTH, 15 + BUTTON_HEIGHT * 2, (irr::s32)GUI_ID_BOUTON::GUI_ID_OPTIONS_BUTTON, L"Options", L"Configure the game" },
	  { 15, 15 + BUTTON_HEIGHT * 2, 15 + BUTTON_WIDTH, 15 + BUTTON_HEIGHT * 3, (irr::s32)GUI_ID_BOUTON::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit the game" },
  };
  MenuState::MenuState() :
	  menuEventReceiver(),
	  _wallpaper(NULL)
  {
  }

  MenuState::~MenuState()
  {
    //this->_wallpaper->drop();
  }

  void MenuState::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_sceneManager = this->_engine->getSceneManager();
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    this->menuEventReceiver.setEngine(this->_engine);
    this->_engine->getDevice()->setEventReceiver(&this->menuEventReceiver);

    if (!(this->_wallpaper = _engine->getDriver()->getTexture(WALLPAPER)))
      throw IndieStudioException();

/*
    this->_gui->addButton(irr::core::rect<irr::s32>(this->_engine->getWindowSize().X / 2, this->_engine->getWindowSize().Y / 4, this->_engine->getWindowSize().X / 2 + 100, this->_engine->getWindowSize().Y / 4 + 50),
			  0, 1, L"New Window", L"Lauche a new window");
*/
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
    this->_gui->drawAll();
    this->_driver->endScene();
  }

  void MenuState::ChangeState(GameEngine *engine,
			      IGameState *state)
  {

  }
}

void is::MenuState::drawButtons()
{
  for (auto &it : BUTTONS)
    {
      it.set(this->_gui->addButton({it.getX(), it.getY(), it.getX2(), it.getY2()},
			    0,
			    it.getId(),
			    it.getText(),
			    it.getHint()));
      it->setUseAlphaChannel(true);
    }
  for (irr::s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
      irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
      col.setAlpha(255);
      _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
    }
}
