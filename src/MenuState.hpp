//
// greg
//

#pragma once

#include <vector>
#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
#include "Button.hpp"
#include "MenuEventReceiver.hpp"
#include "IndieStudioException.hpp"

namespace is
{
  class MenuState : public IGameState
  {
   public:
	    MenuState();
    virtual ~MenuState();
    virtual void Init(GameEngine *engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void Resume(void);
    virtual void HandleEvents(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void ChangeState(GameEngine *engine,
			     IGameState *state);

   protected:
    static const irr::io::path			WALLPAPER;
    static const irr::s32		 	BUTTON_WIDTH;
    static const irr::s32		 	BUTTON_HEIGHT;
    
    MenuEventReceiver				_menuEventReceiver;
    GameEngine 					*_engine;
    irr::video::IVideoDriver			*_driver;
    irr::scene::ISceneManager			*_sceneManager;
    irr::gui::IGUIEnvironment			*_gui;

    irr::video::ITexture* 			_wallpaper;
    std::vector<is::Button> 			_buttons;
    std::vector<irr::gui::IGUIStaticText*> 	_text;
    irr::gui::IGUIStaticText			*_errorMsg;
    irr::gui::IGUIFont            *_font;

    void					drawButtons();
  };
}