//
// greg
//

#include <MenuState.hpp>
#include "IntroState.hpp"

namespace is
{
    IntroState::IntroState() : _parserMap("map01.txt"), _introEventReceiver()
    {
    }
    IntroState::~IntroState()
    {
    }
    void                        IntroState::Init(GameEngine *engine)
    {
	std::cerr << "gros fdp" << std::endl;
        this->_engine = engine;
        this->_driver = this->_engine->getDriver();
        this->_sceneManager = this->_engine->getSceneManager();
        this->_introEventReceiver.setEngine(this->_engine);
    	this->_sceneManager = _sceneManager->createNewSceneManager(false);
      	engine->setSceneManager(_sceneManager);
        this->_engine->getDevice()->setEventReceiver(&this->_introEventReceiver);
        _mapi = _parserMap.getVector();
        _map = std::make_shared<is::map>(_driver, _sceneManager, _mapi);
	_cam = new Camera(_sceneManager, this->_driver, SPLASHSCREEN, _engine);
    	_cam->setTextIntro();
         _cam->setAnimation1();
      std::cerr << "gros fdp" << std::endl;
    }

    void                        IntroState::Cleanup()
    {
      std::cerr << "Cleaning up" << std::endl;
      delete _cam;
      std::cerr << "Cleaning up" << std::endl;
      _sceneManager->clear();
      std::cerr << "Cleaning up" << std::endl;
    }
    void                        IntroState::Pause()
    {
    }
    void                        IntroState::Resume()
    {
    }
    void                        IntroState::HandleEvents()
    {
      std::cerr << "gros fdp0" << std::endl;
    }
    void                        IntroState::Update()
    {
      std::cerr << "gros fdp1" << std::endl;
      _cam->setSplashScreen();
      std::cerr << "gros fdp1" << std::endl;
    }
    void                        IntroState::Draw()
    {
      std::cerr << "gros fdp2" << std::endl;
      this->_driver->beginScene();
      _sceneManager->drawAll();
      this->_driver->endScene();
      if (this->_cam->checkEndIntro())
	_engine->ChangeState(new is::MenuState);
    }


void                        IntroState::ChangeState(GameEngine *engine, IGameState *state)
    {
        this->_engine->ChangeState(state);
    }
}