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
    };

    ChooseSkinStateEventReceiver();
    ~ChooseSkinStateEventReceiver();

    virtual bool 					OnEvent(const irr::SEvent &event);
    void						init(SContext *sContext);

   private:
    SContext						*_context;
  };
}

#endif //CPP_INDIE_STUDIO_CHOOSESKINSTATEEVENTRECEIVER_HPP
