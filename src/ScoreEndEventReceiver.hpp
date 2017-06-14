//
// greg
//

#pragma once

#include <vector>
#include "irrlicht.h"
#include "GameEngine.hpp"


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

namespace is
{
  class                 ScoreEndEventReceiver : public irr::IEventReceiver
  {
   public:
                                                ScoreEndEventReceiver();
    virtual                                     ~ScoreEndEventReceiver();
    virtual bool 		                        OnEvent(const irr::SEvent& event);
    void				                        setDevice(irr::IrrlichtDevice *device);
    void				                        setEngine(GameEngine *engine);
   private:
    irr::IrrlichtDevice				            *_device;
    GameEngine					                *_engine;
    std::vector<std::shared_ptr<IGameState>> 	_states;
  };
}