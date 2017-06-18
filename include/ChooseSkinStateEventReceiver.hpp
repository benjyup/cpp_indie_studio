//
// Created by vincent on 18/06/17.
//

#ifndef CPP_INDIE_STUDIO_CHOOSESKINSTATEEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_CHOOSESKINSTATEEVENTRECEIVER_HPP

#include "irrlicht.h"
#include "GameEngine.hpp"

namespace is
{
  class ChooseSkinStateEventReceiver : public irr::IEventReceiver
  {
   public:
    struct SContext
    {
      GameEngine 					*engine;
      irr::u32 						current_index;
      std::vector<std::pair<irr::scene::IAnimatedMeshSceneNode *,
	      std::vector<irr::video::ITexture*>>>	*meshes;
      bool						apply;
    };

    ChooseSkinStateEventReceiver();
    ~ChooseSkinStateEventReceiver();

    virtual bool 					OnEvent(const irr::SEvent &event);
    void						init(SContext *sContext);

   private:
    SContext						*_context;

    void						_nextMesh();
    void						_prevMesh();
    void						_nextTexture();
    void						_prevTexture();
    void						_apply();

  };
}

#endif //CPP_INDIE_STUDIO_CHOOSESKINSTATEEVENTRECEIVER_HPP
