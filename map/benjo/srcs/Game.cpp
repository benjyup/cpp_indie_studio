//
// Created by kyxo on 5/24/17.
//

#include "Game.hpp"
#include "Fire.hpp"
#include "map.hpp"
#include "PlanetSystem.hpp"

static std::vector<int>        mapi; // =
	// {
	// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	// 	1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1,
	// 	1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1,
	// 	1, 2, 1, 2, 1, 0, 0, 2, 0, 0, 0, 0, 1, 2, 1,
	// 	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	// 	1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
	// 	1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	// 	1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 1,
	// 	1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	// 	1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
	// 	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	// 	1, 2, 1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 2, 1,
	// 	1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1,
	// 	1, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 1,
	// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	// };

namespace is
{
  Game::Game(): _parserMap("map01.txt")
  {}

  Game::~Game()
  {}

  void Game::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_sceneManager = this->_engine->getSceneManager();
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    this->_engine->getDevice()->getCursorControl()->setVisible(false);
    mapi = _parserMap.getVector();
    _map = std::make_shared<is::map>(_driver, _sceneManager, mapi);
    Fire                fire(_sceneManager, _driver, irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, 0.5 * SCALE), TOP);
    Fire                fire2(_sceneManager, _driver, irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, 13.5 * SCALE), TOP);
    Fire	        fire3(_sceneManager, _driver, irr::core::vector3df(12.5 * SCALE, 0.5 * SCALE, 0.5 * SCALE), TOP);
    Fire	        fire4(_sceneManager, _driver, irr::core::vector3df(12.5 * SCALE, 0.5 * SCALE, 13.5 * SCALE), TOP);
    PlanetSystem	PlanetR(_sceneManager, _driver, "./gfx/particlered.bmp", 800.0f, 0.001f);
    PlanetSystem	PlanetW(_sceneManager, _driver, "./gfx/particlewhite.bmp", 600.0f, 0.0009f);
    PlanetSystem	PlanetG(_sceneManager, _driver, "./gfx/particlegreen.jpg", 400.0f, 0.0008f);

  }

  void Game::Cleanup(void)
  {

  }

  void Game::Pause(void)
  {
  }

  void Game::Resume(void)
  {

  }

  void Game::HandleEvents(void)
  {
  }

  void Game::Update(void)
  {
  }

  void Game::Draw(void)
  {
    unsigned int i;
    this->_driver->beginScene();
    _sceneManager->drawAll();
    this->_driver->endScene();
  }

  void Game::ChangeState(GameEngine *engine,
			 IGameState *state)
  {
    this->_engine->ChangeState(state);
  }
}
