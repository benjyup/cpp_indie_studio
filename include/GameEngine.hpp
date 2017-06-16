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
#include "Options.hpp"

namespace is {
  class GameEngine : public IGameEngine {
   public:
    GameEngine(const std::string &title, int width = 1920, int height = 1080,
	       int bpp = 0, bool fullscreen = true);
    ~GameEngine();

    virtual void ChangeState(IGameState *state);

    virtual void PushState(IGameState *state);

    virtual void PopState(void);

    virtual void HandleEvents(void);

    virtual void Update(void);

    virtual void Draw(void);

    virtual void Quit(void);

    virtual bool Running(void);

    irr::IrrlichtDevice				*getDevice(void) const;
    irr::video::IVideoDriver			*getDriver(void) const;
    irr::gui::IGUIEnvironment			*getGuiEnv(void) const;
    irr::scene::ISceneManager			*getSceneManager(void) const;
    std::vector<std::shared_ptr<IGameState>> 	getState() const;
    const irr::core::vector2d<int>		&getWindowSize() const;
    Options					&getOptions();

   private:
    std::vector<std::shared_ptr<IGameState>>	_states;
    irr::IrrlichtDevice				*_device;
    irr::video::IVideoDriver			*_driver;
    irr::gui::IGUIEnvironment           	*_guienv;
    irr::scene::ISceneManager			*_smgr;
    irr::core::vector2d<int>			_windowSize;
    bool 					_running;
    bool 					_fullscreen;
    Options					_options;

    virtual void 				Init(const char *title, int width = 640, int height = 480,
						     int bpp = 0, bool fullscreen = false);
    virtual void 				Cleanup();

    GameEngine(const GameEngine &);
    GameEngine                        operator=(const GameEngine &);
  };
}
#endif //CPP_INDIE_STUDIO_GAMEENGINE_HPP
