//
// Created by jeanadrien on 09/05/17.
//

#ifndef CPP_INDIE_STUDIO_GAMEENGINE_HPP
#define CPP_INDIE_STUDIO_GAMEENGINE_HPP

# include <vector>
# include <string>
# include <memory>
# include "irrlicht.h"
# include "IGameEngine.hpp"

namespace is {
  class GameEngine : public IGameEngine {
   public:
    GameEngine(const std::string &title, int width = 640, int height = 480,
	       int bpp = 0, bool fullscreen = false);
    ~GameEngine();

    virtual void ChangeState(IGameState *);

    virtual void PushState(IGameState *);

    virtual void PopState();

    virtual void HandleEvents();

    virtual void Update();

    virtual void Draw();

    virtual void Quit(); //{m_running = false;}

    virtual bool Running();// {return (m_running);}

    irr::IrrlichtDevice					*getDevice(void) const;
    irr::video::IVideoDriver				*getDriver(void) const;
    const std::shared_ptr<irr::gui::IGUIEnvironment>	getGuiEnv(void) const;
    const std::shared_ptr<irr::scene::ISceneManager>	getSceneManager(void) const;

   private:
    std::vector<IGameState *> 	_states;
    irr::IrrlichtDevice 	*_device;
    irr::video::IVideoDriver 	*_driver;
    irr::gui::IGUIEnvironment	*_guienv;
    irr::scene::ISceneManager	*_smgr;

    bool 			_running;
    bool 			_fullscreen;

    virtual void 		Init(const char *title, int width = 640, int height = 480,
				     int bpp = 0, bool fullscreen = false);
    virtual void 		Cleanup();

    GameEngine(const GameEngine &);
    GameEngine                        operator=(const GameEngine &);
  };
}
#endif //CPP_INDIE_STUDIO_GAMEENGINE_HPP
