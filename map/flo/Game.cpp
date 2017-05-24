//
// Created by kyxo on 5/24/17.
//

#include "Game.hpp"

static std::vector<int>        mapi =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1,
		1, 2, 1, 2, 1, 0, 0, 2, 0, 0, 0, 0, 1, 2, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 2, 1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 2, 1,
		1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

namespace is
{
  Game::Game()
  {}

  Game::~Game()
  {}

  void Game::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_sceneManager = this->_engine->getSceneManager();
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    _map = std::make_shared<is::map>(_driver, _sceneManager, mapi);
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