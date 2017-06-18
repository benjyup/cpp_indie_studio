//
// greg
//

#include <MenuState.hpp>
#include "IntroState.hpp"

namespace is
{
    IntroState::IntroState() : _change(CHANGE::NONE), _parserMap("map01.txt"), _introEventReceiver(_change)
    {
    }
    IntroState::~IntroState()
    {
    }

    void                        IntroState::Init(GameEngine *engine)
    {
        this->_engine = engine;
        this->_engine->getDevice()->setEventReceiver(NULL);
        this->_driver = this->_engine->getDriver();
        this->_sceneManager = this->_engine->getSceneManager();
        this->_introEventReceiver.setEngine(this->_engine);
    	this->_sceneManager = _sceneManager->createNewSceneManager(false);
      	engine->setSceneManager(_sceneManager);
      _mapi = _parserMap.getVector();
        _map = std::make_shared<is::map>(_driver, _sceneManager, _mapi);
	    _cam = new Camera(_sceneManager, this->_driver, SPLASHSCREEN, _engine);
    	_cam->setTextIntro();
      _cam->setAnimation1();
      this->_engine->getDevice()->setEventReceiver(&this->_introEventReceiver);
    }

    void                        IntroState::Cleanup()
    {
      delete _cam;
      this->_engine->getDevice()->setEventReceiver(NULL);
    }
    void                        IntroState::Pause()
    {
    }
    void                        IntroState::Resume()
    {
      this->_engine->getDevice()->setEventReceiver(&this->_introEventReceiver);
    }
    void                        IntroState::HandleEvents()
    {
      if (this->_cam->checkEndIntro() || _change == CHANGE::MENU)
	_engine->ChangeState(new is::MenuState);
    }
    void                        IntroState::Update()
    {
      _cam->setSplashScreen();
    }
    void                        IntroState::Draw()
    {
      this->_driver->beginScene();
      _sceneManager->drawAll();
      this->_driver->endScene();
    }


void                        IntroState::ChangeState(GameEngine *engine, IGameState *state)
    {
        this->_engine->ChangeState(state);
    }
}