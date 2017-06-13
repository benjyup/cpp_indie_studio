//
// Created by kyxo on 5/24/17.
//

#include <include/Camera.hpp>
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
    _bomb = std::make_shared<is::Bombs>(_map.get(), _driver, _sceneManager);
    _bombs = std::make_shared<is::BombsT>(*(_map.get()), *_driver, *_sceneManager);
    _opt = _engine->getOptions();
    _char[0] = std::make_shared<is::Character>(Character((_sceneManager->getMesh("./chef/tris.md2")), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(3 * SCALE - SCALE / 2, SCALE, 2 * SCALE)));
    _char[1] = std::make_shared<is::Character>(Character((_sceneManager->getMesh("./chef/tris.md2")), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(10 * SCALE, SCALE, 10 * SCALE)));
    _powerUp = std::make_shared<is::PowerUp>(PowerUp((_sceneManager->getMesh("./powersUp/mushroom/supermushroom.obj")), _driver->getTexture("./powersUp/mushroom/t0081_0.png"), _sceneManager, core::vector3df(100, 0, 100)));
    _receiver.init(_opt, _char);
    _engine->getDevice()->setEventReceiver(&_receiver);
    Vector3d	v(5 * SCALE + SCALE / 2 - SCALE, 0, 3 * SCALE + SCALE / 2 - SCALE);
    //_bomb = std::make_shared<is::Bombs>(_map.get(), _driver, _sceneManager);
 //   Vector3d	v(3, 3, 1);
//    _bomb->putBomb(v, 1);
    _bombs->putBomb({5, 3, 0}, 10000);
    //Camera	cam(_sceneManager, MENU, _engine);
    //cam.setSplashScreen();
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
      _powerUp->update();
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
