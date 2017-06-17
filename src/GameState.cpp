//
// Created by kyxo on 5/24/17.
//

#include <Camera.hpp>
#include <GenerateMap.hpp>
#include <PauseState.hpp>
#include "GameState.hpp"

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

  std::mutex					GameState::DRAW_MUTEX;

  GameState::GameState(): _parserMap("map01.txt"), _genMap("map02.txt")
  {}

  GameState::~GameState()
  {}

  void GameState::Init(GameEngine *engine)
  {
    this->_engine = engine;
    this->_sceneManager = this->_engine->getSceneManager()->createNewSceneManager(false);
    this->_engine->setSceneManager(_sceneManager);
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    this->_engine->getDevice()->getCursorControl()->setVisible(false);
    //mapi = _parserMap.getVector();
    mapi = _genMap.getMap();
    _map = std::make_shared<is::map>(_driver, _sceneManager, mapi);
    _powManager = std::make_shared<is::PowerUpManager>(PowerUpManager(*_sceneManager, *_driver, _map.get()));
    _bombs = std::make_shared<is::BombsManager>(*(_map.get()), *_driver, *_sceneManager, *_powManager);
    _opt = &_engine->getOptions();
    _char.push_back(std::make_shared<is::Character>(_sceneManager->getMesh("./chef/tris.md2"), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(1 * SCALE + 7, 10, 1 * SCALE + 7), _receiver, _opt->getP1Config(),
						    *_bombs.get()));
    _char.push_back(std::make_shared<is::Character>(_sceneManager->getMesh("./chef/tris.md2"), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(3 * SCALE - SCALE / 2, 3, 2 * SCALE), _receiver, _opt->getP2Config(),
						    *_bombs.get()));
    for (auto &i : _char)
      _map->addCollision(i.get()->getMesh());
    _powManager->newPow(irr::core::vector3df(7, 7, 0));
    _engine->getDevice()->setEventReceiver(&_receiver);
    _receiver.init();
    Vector3d	v(5 * SCALE + SCALE / 2 - SCALE, 0, 3 * SCALE + SCALE / 2 - SCALE);
    //_bomb = std::make_shared<is::Bombs>(_map.get(), _driver, _sceneManager);
    //   Vector3d	v(3, 3, 1);
    //_bomb->putBomb(v, 1);
    _cam = std::make_shared<Camera>(_sceneManager, _driver, MENU, _engine);
    //_cam->setMenuMode();
    _cam->setInGameMode();
    changing = false;
  }

  void GameState::Cleanup(void)
  {

  }

  void GameState::Pause(void)
  {
  }

  void GameState::Resume(void)
  {
    std::cerr << "Reprise" << std::endl;
    changing  = false;
    _engine->getDevice()->getCursorControl()->setVisible(false);
    _engine->getDevice()->setEventReceiver(&this->_receiver);
  }

  void GameState::HandleEvents(void)
  {
    if (_receiver.isKeyDown(irr::KEY_ESCAPE) && changing == false)
      {
	_receiver.init();
	changing = true;
	_engine->PushState(new PauseState);
      }
  }

  void GameState::Update(void)
  {
    // A changer
    _char.remove_if([&](auto &Char) {
      if (!Char->getAlive())
	  Char->die();
      return !Char->getAlive();
    });
    for (auto &i : _char)
      {
	i->update(_powManager.get(), _map.get());
	i->moove();
      }
//      _char[0]->update(_powManager.get(), _map.get());
//      _char[1]->update(_powManager.get(), _map.get());
  }

  void GameState::Draw(void)
  {
    this->_driver->beginScene();
//      this->_char[0]->moove();
//    this->_char[1]->moove();
    this->_bombs->checkBombsStatus();
    _sceneManager->drawAll();
    _map->printMap();
    //_cam->draw();
    //_map->draw();
    this->_driver->endScene();
  }

  void GameState::ChangeState(GameEngine *engine,
			      IGameState *state)
  {
    this->_engine->ChangeState(state);
  }
}
