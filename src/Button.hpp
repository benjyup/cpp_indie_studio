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

   private:
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
