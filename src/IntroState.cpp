//
// greg
//

#include "IntroState.hpp"

namespace is
{
    IntroState::IntroState() : _parserMap("map01.txt")
    {
    }
    IntroState::~IntroState()
    {
    }
    void                        IntroState::Init(GameEngine *engine)
    {
        this->_engine = engine;
        this->_driver = this->_engine->getDriver();
        this->_sceneManager = this->_engine->getSceneManager();
        _mapi = _parserMap.getVector();
        _map = std::make_shared<is::map>(_driver, _sceneManager, _mapi);
        Camera	cam(_sceneManager, this->_driver, MENU, _engine);
        cam.setSplashScreen();
    }
    void                        IntroState::Cleanup()
    {
    }
    void                        IntroState::Pause()
    {
    }
    void                        IntroState::Resume()
    {
    }
    void                        IntroState::HandleEvents()
    {
    }
    void                        IntroState::Update()
    {
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