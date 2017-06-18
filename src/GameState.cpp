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

  GameState::GameState(): _change(CHANGE::NONE), _parserMap("map01.txt"), _genMap("map02.txt"), _receiver(_change)
  {
    std::cerr << "initing game" << std::endl;
  }

  GameState::~GameState()
  {}

  void GameState::Init(GameEngine *engine)
  {
    this->_engine = engine;
    std::cerr << "initing game1" << std::endl;
    _engine->getDevice()->setEventReceiver(NULL);
    this->_sceneManager = this->_engine->getSceneManager()->createNewSceneManager(false);
    this->_engine->setSceneManager(_sceneManager);
    this->_driver = this->_engine->getDriver();
    this->_gui = this->_engine->getGuiEnv();
    this->_engine->getDevice()->getCursorControl()->setVisible(false);
    //mapi = _parserMap.getVector();
    mapi = _genMap.getMap();
    _map = std::make_shared<is::map>(_driver, _sceneManager, mapi);
    _powManager = std::make_shared<is::PowerUpManager>(PowerUpManager(*_sceneManager, *_driver, _map.get()));
    _map.get()->set_pm(_powManager.get());
    _bombs = std::make_shared<is::BombsManager>(*(_map.get()), *_driver, *_sceneManager, *_powManager);
    _opt = &_engine->getOptions();
    _char.push_back(std::make_shared<is::Character>(_sceneManager->getMesh("./chef/tris.md2"), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df(1 * SCALE + 7, 2, 1 * SCALE + 7), _receiver, _opt->getP1Config(),
						    *_bombs.get(), 1));
    _char.push_back(std::make_shared<is::Character>(_sceneManager->getMesh("./chef/tris.md2"), _driver->getTexture("./chef/chef.pcx"), _sceneManager, core::vector3df((BLOCK - 2) * SCALE - 7, 2, (BLOCK - 2) * SCALE - 7), _receiver, _opt->getP2Config(),
						    *_bombs.get(), 2));
    for (auto &i : _char)
      _map->addCollision(i.get()->getMesh());
    _receiver.init();
    Vector3d	v(5 * SCALE + SCALE / 2 - SCALE, 0, 3 * SCALE + SCALE / 2 - SCALE);

    _cam = std::make_shared<Camera>(_sceneManager, _driver, MENU, _engine);
    //_cam->setMenuMode();
    _cam->setInGameMode();
    changing = false;
    _engine->getDevice()->setEventReceiver(&_receiver);
    std::cerr << "initing game2" << std::endl;
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
    _change = CHANGE::NONE;
    changing  = false;
    _receiver.init();
    _engine->getDevice()->getCursorControl()->setVisible(false);
    _engine->getDevice()->setEventReceiver(&this->_receiver);
  }

  void GameState::HandleEvents(void)
  {
    if (_receiver.isKeyDown(irr::KEY_ESCAPE) && changing == false)
      {
	_receiver.init();
	changing = true;
	_change = CHANGE::PAUSE;
      }
    for (auto &i : _char)
      {
	i->update(_powManager.get(), _map.get());
	i->moove();
      }
    if (_change == CHANGE::PAUSE)
      _engine->PushState(new PauseState);
  }

  void GameState::Update(void)
  {
    // A changer
    _char.remove_if([&](auto &Char) {
      if (!Char->getAlive())
	Char->die();
      return !Char->getAlive();
    });
    this->_bombs->checkBombsStatus(_char);
//    _bombs->addCollision(_char);
    _powManager->update();
//      _char[0]->update(_powManager.get(), _map.get());
//      _char[1]->update(_powManager.get(), _map.get());
  }

  void GameState::Draw(void)
  {
    this->_driver->beginScene();
    _sceneManager->drawAll();
//    _map->printMap();
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