//
// greg
//

#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
#include "GameEngine.hpp"
#include "ParseMap.hpp"
#include "map.hpp"
#include "GenerateMap.hpp"
#include "Camera.hpp"
#include "Fire.hpp"
#include "PlanetSystem.hpp"

namespace is 
{
    class                       IntroState : public IGameState
    {
        public:
        IntroState();
        virtual                 ~IntroState();
        virtual void            Init(GameEngine *engine);
        virtual void            Cleanup();
        virtual void            Pause();
        virtual void            Resume();
        virtual void            HandleEvents();
        virtual void            Update();
        virtual void            Draw();
        virtual void            ChangeState(GameEngine *engine, IGameState *state);
        private:
        GameEngine                                        *_engine;
        irr::video::IVideoDriver			              *_driver;
        irr::scene::ISceneManager			              *_sceneManager;
        std::vector<int>                                  _mapi;
        ParseMap	    				                  _parserMap;
        std::shared_ptr<map>			                  _map;
    };
}