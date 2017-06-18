//
// Created by vincent on 18/06/17.
//

#ifndef CPP_INDIE_STUDIO_CHOOSESKINSTATE_HPP
#define CPP_INDIE_STUDIO_CHOOSESKINSTATE_HPP


#include <IGameState.hpp>
#include <ChooseSkinStateEventReceiver.hpp>
#include "Button.hpp"

namespace is {
  class ChooseSkinState : public IGameState
  {
   public:
    ChooseSkinState(irr::u32 player);
   ~ChooseSkinState();

    virtual void Resume(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void Init(GameEngine *engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void HandleEvents(void);
    virtual void ChangeState(GameEngine *engine, IGameState *state);

   private:
    static const std::vector<std::pair<std::string, std::vector<std::string>>>	MESH_PATH;
    static const std::vector<std::pair<std::string, std::string>>		BUTTON_GFX_PATH;

    irr::gui::IGUIEnvironment							*_gui;
    irr::video::IVideoDriver							*_driver;
    irr::scene::ISceneManager   						*_sceneManager;
    is::Options									*_options;
    std::vector<std::pair<irr::scene::IAnimatedMeshSceneNode *, std::vector<irr::video::ITexture*>>>	_meshes;
    std::vector<is::Button>							_buttons;
    ChooseSkinStateEventReceiver						_receiver;
    ChooseSkinStateEventReceiver::SContext					_context;
    irr::u32 									_player;

    void 									_drawButtons();
    void									_drawMeshes();

  };
}

#endif //CPP_INDIE_STUDIO_CHOOSESKINSTATE_HPP
