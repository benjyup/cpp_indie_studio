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

    enum class GUI_ID_BOUTON : irr::s32
    {
      GUI_ID_PLAY_BUTTON = 0,
      GUI_ID_OPTIONS_BUTTON,
      GUI_ID_QUIT_BUTTON,
      GUI_ID_LENGTH
    };

   private:
    static const irr::io::path			WALLPAPER;
    static const irr::s32		 	BUTTON_WIDTH;
    static const irr::s32		 	BUTTON_HEIGHT;
    static std::vector<is::Button> 		BUTTONS;

    MenuEventReceiver				menuEventReceiver;
    GameEngine 					*_engine;
    irr::video::IVideoDriver			*_driver;
    irr::scene::ISceneManager			*_sceneManager;
    irr::gui::IGUIEnvironment			*_gui;

    irr::video::ITexture* 			_wallpaper;

    void					drawButtons();
  };
}