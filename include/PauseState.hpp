//
// greg
//

#pragma once

#include <map>
#include <IGameState.hpp>
#include "MenuState.hpp"
#include "PauseEventReceiver.hpp"

class                                                   PauseEventReceiver;

namespace is
{
  class                                                 PauseState : public MenuState
  {
   public:

                                                        PauseState();
    virtual                                             ~PauseState();
    virtual void 					                    Init(is::GameEngine *engine);
    virtual void 					                    Resume(void);
    virtual void 					                    HandleEvents(void);

   private:
    CHANGE 							    _change;
    PauseEventReceiver				                    _PauseEventReceiver;
  };
}