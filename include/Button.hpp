//
// Created by vincent on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_BUTTON_HPP
#define CPP_INDIE_STUDIO_BUTTON_HPP

#include <regex>
#include "irrlicht.h"
#include "Options.hpp"

namespace is
{
  class Button
  {
   public:

    enum class GUI_ID_BOUTON : irr::s32
    {
      GUI_ID_MOVE_ACTION_BUTTON = 0,
      GUI_ID_MOVE_FORWARD_BUTTON,
      GUI_ID_MOVE_BACKWARD_BUTTON,
      GUI_ID_MOVE_RIGHT_BUTTON,
      GUI_ID_MOVE_LEFT_BUTTON,
      GUI_ID_TMP_MOVE_ACTION_BUTTON,
      GUI_ID_TMP_MOVE_FORWARD_BUTTON,
      GUI_ID_TMP_MOVE_BACKWARD_BUTTON,
      GUI_ID_TMP_MOVE_RIGHT_BUTTON,
      GUI_ID_TMP_MOVE_LEFT_BUTTON,
      GUI_ID_CHANGE_PLAYER1_BUTTON,
      GUI_ID_CHANGE_PLAYER2_BUTTON,
      GUI_ID_APPLY_BUTTON,
      GUI_ID_CANCEL_BUTTON,
      GUI_ID_PLAY_BUTTON,
      GUI_ID_OPTIONS_BUTTON,
      GUI_ID_QUIT_BUTTON,
      GUI_ID_REPLAY_BUTTON,
      GUI_ID_MENU_BUTTON,
      GUI_ID_RESUME_BUTTON,
      GUI_ID_WALLPAPER_BUTTON,
      GUI_ID_PRESS_BUTTON,
      GUI_ID_ADD_POS1,
      GUI_ID_ADD_POS2,
      GUI_ID_ADD_POS3,
      GUI_ID_ADD_POS4,
      GUI_ID_ADD_PLAYER,
      GUI_ID_ADD_AI,
      GUI_ID_ADD_PLAY,
      GUI_ID_WINNER,
      GUI_ID_DELETE_PLAYER,
      GUI_ID_DELETE_AI,
      GUI_ID_LOAD_BUTTON,
      GUI_ID_SAVE_BUTTON,
      GUI_ID_SOUND_ON_BUTTON,
      GUI_ID_SOUND_OFF_BUTTON,
      GUI_ID_LEFT_ARROW,
      GUI_ID_RIGHT_ARROW,
      GUI_ID_UP_ARROW,
      GUI_ID_DOWN_ARROW,
      GUI_ID_SKIN_APPLY,
      GUI_ID_PLAYER1_WINNER,
      GUI_ID_PLAYER2_WINNER,
      GUI_ID_IA1_WINNER,
      GUI_ID_IA2_WINNER,
      GUI_ID_BORDER_LEFT,
      GUI_ID_BORDER_RIGHT,
      GUI_ID_TOP,
      GUI_ID_LENGTH,
    };

    static const std::map<GUI_ID_BOUTON, Options::MOVES>	BUTTON_TO_MOVE;

    Button(const irr::s32 x,
	   const irr::s32 y,
	   const irr::s32 x2,
	   const irr::s32 y2,
	   const irr::s32 id,
	   const irr::core::stringw = "",
	   const irr::core::stringw = "");
    Button(const Button &other);
    ~Button();

    Button			&operator=(const Button &other);
    irr::gui::IGUIButton	*operator->() const;

    irr::s32			getX() const;
    irr::s32 			getX2() const;
    irr::s32 			getY() const;
    irr::s32 			getY2() const;
    irr::s32 			getId() const;
    void 			set(irr::gui::IGUIButton *);


    const irr::core::stringw	getText() const;
    const irr::core::stringw	getHint() const;
    irr::gui::IGUIButton      *getButton() const;
    int                       getPress() const;
    void                      setPress(int press);
   private:
    int           _press;
    irr::s32			_x;
    irr::s32			_x2;
    irr::s32			_y;
    irr::s32			_y2;
    irr::s32			_id;
    irr::core::stringw 		_text;
    irr::core::stringw 		_hint;
    irr::gui::IGUIButton	*_button;
  };

}

#endif //CPP_INDIE_STUDIO_BUTTON_HPP
