//
// Created by jeanadrien on 09/05/17.
//

# include <irrlicht.h>
#include "GameEngine.hpp"

is::GameEngine::GameEngine(const std::string &title, int width, int height,
			   int bpp, bool fullscreen)
{
  this->Init(title.c_str(), width, height, bpp, fullscreen);
}

is::GameEngine::~GameEngine()
{

}

void is::GameEngine::Init(const char* title, int width, int height,
			  int bpp, bool fullscreen)
{
  this->_device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(width, height), bpp,
				    fullscreen, false, false, 0);
  this->_driver = this->_device->getVideoDriver();
  this->_smgr = this->_device->getSceneManager();
  this->_guienv = this->_device->getGUIEnvironment();
  irr::core::stringw wStr(title);
  this->_device->setWindowCaption(wStr.c_str());

  this->_fullscreen = fullscreen;
  this->_running = true;

  printf("is::GameEngine Init\n");
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
  // cleanup the all states
  while ( !this->_states.empty() ) {
      this->_states.back()->Cleanup();
      this->_states.pop_back();
    }

  // switch back to windowed mode so other
  // programs won't get accidentally resized
  this->_device->drop();
  printf("is::GameEngine Cleanup\n");

}

void is::GameEngine::ChangeState(IGameState* state)
{
  // cleanup the current state
  if ( !this->_states.empty() ) {
      this->_states.back()->Cleanup();
      this->_states.pop_back();
    }

  // store and init the new state
  this->_states.push_back(state);
  this->_states.back()->Init(this);
}

void is::GameEngine::PushState(IGameState* state)
{
  // pause current state
  if ( !this->_states.empty() ) {
      this->_states.back()->Pause();
    }

  // store and init the new state
  this->_states.push_back(state);
  this->_states.back()->Init(this);
}

void is::GameEngine::PopState()
{
  // cleanup the current state
  if ( !this->_states.empty() ) {
      this->_states.back()->Cleanup();
      this->_states.pop_back();
    }

  // resume previous state
  if ( !this->_states.empty() ) {
      this->_states.back()->Resume();
    }
}


void is::GameEngine::HandleEvents()
{
  // let the state handle events
  if (!this->_states.empty())
    this->_states.back()->HandleEvents(this);
}

void is::GameEngine::Update()
{
  // let the state update the game
  if (!this->_states.empty())
    this->_states.back()->Update(this);
}

void is::GameEngine::Draw()
{
  // let the state draw the screen
  if (!this->_states.empty())
    this->_states.back()->Draw(this);
}

irr::IrrlichtDevice 		*is::GameEngine::getDevice(void) const
{
  return (this->_device);
}

irr::video::IVideoDriver 	*is::GameEngine::getDriver(void) const
{
  return (this->_driver);
}

const std::shared_ptr<irr::gui::IGUIEnvironment> is::GameEngine::getGuiEnv(void) const
{
  return (std::shared_ptr<irr::gui::IGUIEnvironment>(this->_guienv));
}

const std::shared_ptr<irr::scene::ISceneManager> is::GameEngine::getSceneManager(void) const
{
  return (std::shared_ptr<irr::scene::ISceneManager>(this->_smgr));
}
