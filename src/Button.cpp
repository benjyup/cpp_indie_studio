//
// Created by vincent on 22/05/17.
//

#include "Button.hpp"

const std::map<is::Button::GUI_ID_BOUTON, is::Options::MOVES>	is::Button::BUTTON_TO_MOVE = {
	{GUI_ID_BOUTON::GUI_ID_MOVE_ACTION_BUTTON, Options::MOVES::MOVE_ACTION },
	{GUI_ID_BOUTON::GUI_ID_MOVE_FORWARD_BUTTON, Options::MOVES::MOVE_UP },
	{GUI_ID_BOUTON::GUI_ID_MOVE_BACKWARD_BUTTON, Options::MOVES::MOVE_DOWN },
	{GUI_ID_BOUTON::GUI_ID_MOVE_RIGHT_BUTTON, Options::MOVES::MOVE_RIGHT },
	{GUI_ID_BOUTON::GUI_ID_MOVE_LEFT_BUTTON, Options::MOVES::MOVE_LEFT },
};


is::Button::Button(const irr::s32 x, const irr::s32 y, const irr::s32 x2, const irr::s32 y2, const irr::s32 id,
		   const irr::core::stringw text, const irr::core::stringw hint) :
	_press(0),
	_x(x),
	_y(y),
	_x2(x2),
	_y2(y2),
	_id(id),
	_text(text),
	_hint(hint),
	_button(NULL)
{

}

is::Button::Button(const is::Button &other) :
	_press(0),
	_x(other._x),
	_y(other._y),
	_x2(other._x2),
	_y2(other._y2),
	_id(other._id),
	_text(other._text),
	_hint(other._hint),
	_button(other._button)
{

}

is::Button::~Button()
{

}

is::Button &is::Button::operator=(const is::Button &other)
{
	this->_press = 0;
  this->_x = other._x;
  this->_y = other._y;
  this->_x2 = other._x2;
  this->_y2 = other._y2;
  this->_id = other._id;
  this->_text = other._text;
  this->_hint = other._hint;
  this->_button = other._button;
  return (*this);
}

irr::s32 is::Button::getX() const
{
  return (this->_x);
}

irr::s32 is::Button::getX2() const
{
  return (this->_x2);
}

irr::s32 is::Button::getY() const
{
  return (this->_y);
}

irr::s32 is::Button::getY2() const
{
  return (this->_y2);
}

const irr::core::stringw is::Button::getText() const
{
  return (this->_text);
}

const irr::core::stringw is::Button::getHint() const
{
  return (this->_hint);
}

irr::s32 is::Button::getId() const
{
  return (this->_id);
}

void is::Button::set(irr::gui::IGUIButton *button)
{
  this->_button = button;
}

irr::gui::IGUIButton *is::Button::operator->() const
{
  return (this->_button);
}

int 										is::Button::getPress() const 
{
	return (this->_press);
}

void 										is::Button::setPress(int press)
{
	_press = press;
}

irr::gui::IGUIButton			*is::Button::getButton() const
{
	return (this->_button);
}
