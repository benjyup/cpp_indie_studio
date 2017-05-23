//
// greg
//

#pragma once

#include <vector>
#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
#include "Button.hpp"

namespace is
{
  class MenuState : public IGameState
  {
   public:




	    MenuState();
    virtual ~MenuState();
    virtual void Init(std::shared_ptr<GameEngine> engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void Resume(void);
    virtual void HandleEvents(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void ChangeState(std::shared_ptr<GameEngine> engine, std::shared_ptr<IGameState> state);

   private:
    static const irr::io::path			WALLPAPER;
    static const irr::s32		 	BUTTON_WIDTH;
    static const irr::s32		 	BUTTON_HEIGHT;
    static std::vector<is::Button> 		BUTTONS;

    enum class GUI_ID_BOUTON : irr::s32
    {
      GUI_ID_PLAY_BUTTON = 0,
      GUI_ID_OPTIONS_BUTTON,
      GUI_ID_QUIT_BUTTON,
      GUI_ID_LENGTH
    };

    std::shared_ptr<GameEngine> _engine;
    irr::video::IVideoDriver	*_driver;
    irr::scene::ISceneManager	*_sceneManager;
    irr::gui::IGUIEnvironment	*_gui;

    irr::video::ITexture* 	_wallpaper;
    irr::video::ITexture* 	_buttonGfx;

    void					drawButtons();
  };
}