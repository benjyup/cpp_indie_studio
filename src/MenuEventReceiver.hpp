//
// Created by vincent on 23/05/17.
//

#pragma once

#include "irrlicht.h"
#include "GameEngine.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

namespace is
{
  class MenuEventReceiver : public irr::IEventReceiver
  {
   public:
    MenuEventReceiver();
    virtual ~MenuEventReceiver();

    virtual bool 		OnEvent(const irr::SEvent& event);
    void			setDevice(irr::IrrlichtDevice *device);
    void			setEngine(GameEngine *engine);

   private:
    irr::IrrlichtDevice		*_device;
    GameEngine			*_engine;

  };

}
