//
// Created by kyxo on 5/24/17.
//

#include <Camera.hpp>
#include "Game.hpp"

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

  std::mutex					Game::DRAW_MUTEX;

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
    _bombs = std::make_shared<is::BombsManager>(*(_map.get()), *_driver, *_sceneManager);
    _opt = _engine->getOptions();
    _char[0] = std::make_shared<is::Character>(_sceneManager->getMesh("./chef/tris.md2"), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(10 * SCALE + 7, 5, 10 * SCALE + 7), _receiver, _opt,
    *_bombs.get());
    _map->addCollision(_char[0].get()->_mesh);
    _char[1] = std::make_shared<is::Character>(_sceneManager->getMesh("./chef/tris.md2"), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(3 * SCALE - SCALE / 2, 5, 2 * SCALE), _receiver, _opt,
    *_bombs.get());
    _map->addCollision(_char[1].get()->_mesh);
    _powManager = std::make_shared<is::PowerUpManager>(PowerUpManager(*_sceneManager, *_driver));
    _powManager->newPow();
    _engine->getDevice()->setEventReceiver(&_receiver);
    Vector3d	v(5 * SCALE + SCALE / 2 - SCALE, 0, 3 * SCALE + SCALE / 2 - SCALE);
    //_bomb = std::make_shared<is::Bombs>(_map.get(), _driver, _sceneManager);
    //   Vector3d	v(3, 3, 1);
    //_bomb->putBomb(v, 1);
    _bombs->putBomb({6, 3, 0}, 10000);
    _bombs->putBomb({7, 3, 0}, 10000);
    _cam = std::make_shared<Camera>(_sceneManager, _driver, MENU, _engine);
   // _cam->setMenuMode();
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
    _powManager->update(_char[0]->getPos());
    _powManager->update(_char[1]->getPos());
  }

  void Game::Draw(void)
  {
    std::unique_lock<std::mutex> lock(DRAW_MUTEX);
    this->_driver->beginScene();
    this->_char[0]->moove();
    this->_bombs->checkBombsStatus();
    _sceneManager->drawAll();
    //_cam->draw();
    //_map->draw();
    this->_driver->endScene();
  }

  void Game::ChangeState(GameEngine *engine,
			 IGameState *state)
  {
    this->_engine->ChangeState(state);
  }
}
