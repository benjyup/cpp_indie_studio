//
// greg
//

#ifndef SCOREEND_HPP
# define SCOREEND_HPP

#include <vector>
#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
#include "Button.hpp"
#include "ScoreEndEventReceiver.hpp"
#include "IndieStudioException.hpp"

namespace is
{
    class ScoreEnd : public IGameState //quand c'est call il faut que le menu soit derrier au cas ou je Pop
    {
        public:
            ScoreEnd();
            virtual                                 ~ScoreEnd();
            virtual void                            Init(GameEngine *engine);
            virtual void                            Cleanup(void);
            virtual void                            Pause(void);
            virtual void                            Resume(void);
            virtual void                            HandleEvents(void);
            virtual void                            Update(void);
            virtual void                            Draw(void);
            virtual void                            ChangeState(GameEngine *engine, IGameState *state);
        private:
            void                                    drawButtons();
            void                                    drawWinner();
            static const irr::s32		 	        BUTTON_WIDTH;
            static const irr::s32		 	        BUTTON_HEIGHT;
            static const std::vector<std::string>   TEXT_END;
            GameEngine                              *_engine;
            irr::video::IVideoDriver			    *_driver;
            irr::scene::ISceneManager			    *_sceneManager;
            irr::gui::IGUIEnvironment			    *_gui;
            std::vector<is::Button> 			    _buttons;
            irr::gui::IGUIFont                      *_font;
            ScoreEndEventReceiver                   _ScoreEndReceiver;
            std::vector<irr::gui::IGUIStaticText*> 	_text;
            irr::video::ITexture* 			        _wallpaper;
    };
}

#endif //SCOREEND_HPP