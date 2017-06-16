//
// greg
//

#ifndef SCOREEND_HPP
# define SCOREEND_HPP

#include <vector>
#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
#include "MenuState.hpp"
#include "Button.hpp"
#include "ScoreEndEventReceiver.hpp"
#include "IndieStudioException.hpp"

namespace is
{
    class ScoreEnd : public MenuState
    {
        public:
            ScoreEnd();
            virtual                                 ~ScoreEnd();
            virtual void                            Init(GameEngine *engine);
            virtual void                            Resume(void);
        private:
            ScoreEndEventReceiver                   _ScoreEndReceiver;
    };
}

#endif //SCOREEND_HPP