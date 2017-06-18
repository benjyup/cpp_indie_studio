//
// Created by jeanadrien on 09/05/17.
//

# include <irrlicht.h>
#include <iostream>
#include "GameEngine.hpp"

is::GameEngine::GameEngine(const std::string &title, int width, int height,
			   int bpp, bool fullscreen) :
	_windowSize(width, height)
{
  this->Init(title.c_str(), width, height, bpp, fullscreen);
}

is::GameEngine::GameEngine(is::GameEngine const &engine)
{
  this->_device = engine.getDevice();
  this->_driver = engine.getDriver();
  this->_guienv = engine.getGuiEnv();
  this->_smgr = engine.getSceneManager();
  this->_states = engine.getState();
}

is::GameEngine::~GameEngine()
{

}

std::vector<std::shared_ptr<is::IGameState>> is::GameEngine::getState() const
{
  return (this->_states);
}

void is::GameEngine::Init(const char* title, int width, int height,
			  int bpp, bool fullscreen)
{
  this->_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(width, height), bpp,
				    fullscreen, false, false, 0);
  this->_driver = this->_device->getVideoDriver();
  this->_smgr = this->_device->getSceneManager();
  this->_guienv = this->_device->getGUIEnvironment();
  irr::core::stringw wStr(title);
  this->_device->setWindowCaption(wStr.c_str());

  this->_fullscreen = fullscreen;
  this->_running = true;
}

void is::GameEngine::Quit()
{
  this->_running = false;
}

bool is::GameEngine::Running()
{
  return (this->_device->run() && this->_running);
}


void is::GameEngine::Cleanup()
{
  while ( !this->_states.empty() ) {
      this->_states.back()->Cleanup();
      this->_states.pop_back();
    }
  this->_device->drop();
}

void is::GameEngine::ChangeState(IGameState *state)
{
  if ( !this->_states.empty() ) {
      this->_states.back()->Cleanup();
      this->_states.pop_back();
    }
  this->_states.emplace_back(state);
  this->_states.back()->Init(this);
}

void is::GameEngine::PushState(IGameState *state)
{
  if ( !this->_states.empty() ) {
      this->_states.back()->Pause();
    }
  this->_states.emplace_back(state);
  this->_states.back()->Init(this);
}

void is::GameEngine::PopState()
{
  if ( !this->_states.empty() ) {
      this->_states.back()->Cleanup();
      this->_states.pop_back();
    }
  if ( !this->_states.empty() ) {
      this->_states.back()->Resume();
    }
}

void is::GameEngine::HandleEvents()
{
  if (!this->_states.empty())
    this->_states.back()->HandleEvents();
}

void is::GameEngine::Update()
{
  if (!this->_states.empty())
    this->_states.back()->Update();
}

void is::GameEngine::Draw()
{
  if (!this->_states.empty())
    this->_states.back()->Draw();
}

irr::IrrlichtDevice 		*is::GameEngine::getDevice(void) const
{
  return (this->_device);
}

irr::video::IVideoDriver 	*is::GameEngine::getDriver(void) const
{
  return (this->_driver);
}

irr::gui::IGUIEnvironment *is::GameEngine::getGuiEnv(void) const
{
  return (this->_guienv);
}

irr::scene::ISceneManager *is::GameEngine::getSceneManager(void) const
{
  return (this->_smgr);
}

const irr::core::vector2d<int> &is::GameEngine::getWindowSize() const
{
  return (this->_windowSize);
}

is::Options &is::GameEngine::getOptions()
{
  return (this->_options);
}

void is::GameEngine::setSceneManager(irr::scene::ISceneManager *sceneManager)
{
	_smgr = sceneManager;
}

Sound	&is::GameEngine::getSound()
{
  return (this->_sound);
}

void is::GameEngine::setWinner(is::Button::GUI_ID_BOUTON const &win)
{
  _winnnerPlayer = win;
}

const is::Button::GUI_ID_BOUTON &is::GameEngine::getWinner()
{
  return _winnnerPlayer;
}
