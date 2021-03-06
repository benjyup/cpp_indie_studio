//
// Created by vincent on 17/06/17.
//

#ifndef CPP_INDIE_STUDIO_CHOOSEPLAYER_HPP
#define CPP_INDIE_STUDIO_CHOOSEPLAYER_HPP

#include <array>
#include <utility>
#include "irrlicht.h"
#include "IGameState.hpp"
#include "Options.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "ChoosePlayerEventReceiver.hpp"

namespace is
{
  class ChoosePlayerState : public IGameState
  {
   public:

    ChoosePlayerState();
    ~ChoosePlayerState();

    virtual void Init(GameEngine *engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void Resume(void);
    virtual void HandleEvents(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void ChangeState(GameEngine *engine, IGameState *state);

   private:
    static std::vector<std::pair<std::string, std::string>>			GFX_PATH;
    static const irr::u32 							PLAY_BUTTON_INDEX;
    static const irr::u32 							VOID_BUTTON_INDEX;
    static const irr::u32 							ADD_BOT_BUTTON_INDEX;
    static const irr::u32 							ADD_PLAYER_BUTTON_INDEX;
    static const irr::u32 							DELETE_BOT_BUTTON_INDEX;
    static const irr::u32 							DELETE_PLAYER_BUTTON_INDEX;

    Options									*_options;
    irr::gui::IGUIEnvironment							*_gui;
    irr::video::IVideoDriver							*_driver;
    std::vector<is::Button>							_buttons;
    irr::scene::ISceneManager   						*_sceneManager;
    std::array<std::pair<irr::video::ITexture *, irr::video::ITexture *>, 4>	_gfxAI;
    std::array<std::pair<irr::video::ITexture *, irr::video::ITexture *>, 2>	_gfxPlayer;
    std::vector<Player>								_players;

    std::array<std::pair<irr::video::ITexture *, irr::video::ITexture *>, 6>	_buttonsTextures;

    irr::u32 									_nbrOfPlayers;
    irr::u32 									_nbrOfAI;
    ChoosePlayerEventReceiver							choosePlayerEventReceiver;
    ChoosePlayerEventReceiver::SContext 					eventContext;


    void			_drawButtons();


  };
}

#endif //CPP_INDIE_STUDIO_CHOOSEPLAYER_HPP
