//
// Created by vincent on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_BUTTON_HPP
#define CPP_INDIE_STUDIO_BUTTON_HPP

#include "irrlicht.h"

namespace is
{
  class Button
  {
   public:
    Button(const irr::s32 x,
	   const irr::s32 y,
	   const irr::s32 x2,
	   const irr::s32 y2,
	   const irr::s32 id,
	   const wchar_t *text = 0,
	   const wchar_t *hint = 0);
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


    const wchar_t 		*getText() const;
    const wchar_t 		*getHint() const;

   private:
    irr::s32			_x;
    irr::s32			_x2;
    irr::s32			_y;
    irr::s32			_y2;
    irr::s32			_id;
    const wchar_t 		*_text;
    const wchar_t 		*_hint;
    irr::gui::IGUIButton	*_button;
  };

}

#endif //CPP_INDIE_STUDIO_BUTTON_HPP
