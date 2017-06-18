//
// Created by vincent on 18/06/17.
//

#ifndef CPP_INDIE_STUDIO_CHOOSESKINSTATE_HPP
#define CPP_INDIE_STUDIO_CHOOSESKINSTATE_HPP


#include <IGameState.hpp>

namespace is {
  class ChooseSkinState : public IGameState
  {
   public:
    ChooseSkinState();
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

    irr::u32 									_current_index;
    irr::gui::IGUIEnvironment							*_gui;
    irr::video::IVideoDriver							*_driver;
    irr::scene::ISceneManager   						*_sceneManager;
    std::vector<std::pair<irr::scene::IAnimatedMeshSceneNode *, std::vector<irr::video::ITexture*>>>	_meshes;
  };
}

#endif //CPP_INDIE_STUDIO_CHOOSESKINSTATE_HPP
