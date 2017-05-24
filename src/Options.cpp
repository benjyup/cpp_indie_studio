//
// Created by vincent on 19/05/17.
//

#include "Options.hpp"

const irr::u8 						is::Options::DEFAULT_VOLUME = 25;
const bool 						is::Options::DEFAULT_FULLSCREEN = false;
const std::map<is::Options::MOVES, irr::EKEY_CODE>	is::Options::DEFAULT_P1_CONFIG = {
	{is::Options::MOVES::MOVE_ACTION, irr::KEY_SPACE},
	{is::Options::MOVES::MOVE_UP, irr::KEY_KEY_Z},
	{is::Options::MOVES::MOVE_DOWN, irr::KEY_KEY_S},
	{is::Options::MOVES::MOVE_RIGHT, irr::KEY_KEY_D},
	{is::Options::MOVES::MOVE_LEFT, irr::KEY_KEY_Q}
};
const std::map<is::Options::MOVES, irr::EKEY_CODE>	is::Options::DEFAULT_P2_CONFIG = {
	{is::Options::MOVES::MOVE_ACTION, irr::KEY_CONTROL},
	{is::Options::MOVES::MOVE_UP, irr::KEY_UP},
	{is::Options::MOVES::MOVE_DOWN, irr::KEY_DOWN},
	{is::Options::MOVES::MOVE_RIGHT, irr::KEY_RIGHT},
	{is::Options::MOVES::MOVE_LEFT, irr::KEY_LEFT}
};

/*
const std::map<irr::EKEY_CODE, const wchar_t*>	KEY_TO_WCHAR = {
	{irr::EKEY_CODE }

};
*/


is::Options::Options() :
	_volume(DEFAULT_VOLUME),
	_fullscreen(DEFAULT_FULLSCREEN),
	_p1Config(DEFAULT_P1_CONFIG),
	_p2Config(DEFAULT_P2_CONFIG)
{

}

is::Options::~Options()
{

}

const std::map<is::Options::MOVES, irr::EKEY_CODE> 	&is::Options::getP1Config() const
{
  return (this->_p1Config);
}

const std::map<is::Options::MOVES, irr::EKEY_CODE> 	&is::Options::getP2Config() const
{
  return (this->_p2Config);
}

irr::u8 is::Options::getVolume() const
{
  return (this->_volume);
}

void is::Options::setVolume(const irr::u8 pourcent)
{
  this->_volume = pourcent;
}

void is::Options::setP1config(const irr::EKEY_CODE key, const is::Options::MOVES move)
{
  this->_p1Config[move] = key ;
}

void is::Options::setP2config(const irr::EKEY_CODE key, const is::Options::MOVES move)
{
  this->_p2Config[move] = key ;
}

irr::core::stringw is::Options::keyToStringw(irr::EKEY_CODE key) const
{
  irr::core::stringw strw;

  switch (key)
    {
      case irr::KEY_CANCEL:    strw = ("CANCEL"); break;
      case irr::KEY_BACK:      strw = ("BACKSPACE"); break;
      case irr::KEY_TAB:       strw = ("TAB"); break;
      case irr::KEY_CLEAR:     strw = ("CLEAR"); break;
      case irr::KEY_RETURN:    strw = ("ENTER"); break;
      case irr::KEY_SHIFT:     strw = ("SHIFT"); break;
      case irr::KEY_CONTROL:   strw = ("CTRL"); break;
      case irr::KEY_MENU:      strw = ("ALT"); break;
      case irr::KEY_PAUSE:     strw = ("PAUSE"); break;
      case irr::KEY_CAPITAL:   strw = ("CAPS LOCK"); break;
      case irr::KEY_ESCAPE:    strw = ("ESC"); break;
      case irr::KEY_SPACE:     strw = ("SPACEBAR"); break;
      case irr::KEY_PRIOR:     strw = ("PAGE UP"); break;
      case irr::KEY_NEXT:      strw = ("PAGE DOWN"); break;
      case irr::KEY_END:       strw = ("END"); break;
      case irr::KEY_HOME:      strw = ("HOME"); break;
      case irr::KEY_LEFT:      strw = ("LEFT ARROW"); break;
      case irr::KEY_UP:        strw = ("UP ARROW"); break;
      case irr::KEY_RIGHT:     strw = ("RIGHT ARROW"); break;
      case irr::KEY_DOWN:      strw = ("DOWN ARROW"); break;
      case irr::KEY_SELECT:    strw = ("SELECT"); break;
      case irr::KEY_PRINT:     strw = ("PRINT"); break;
      case irr::KEY_EXECUT:    strw = ("EXECUTE"); break;
      case irr::KEY_SNAPSHOT:  strw = ("PRINT SCREEN"); break;
      case irr::KEY_INSERT:    strw = ("INSERT"); break;
      case irr::KEY_DELETE:    strw = ("DELETE"); break;
      case irr::KEY_HELP:      strw = ("HELP"); break;
      case irr::KEY_KEY_0:     strw = ("0"); break;
      case irr::KEY_KEY_1:     strw = ("1"); break;
      case irr::KEY_KEY_2:     strw = ("2"); break;
      case irr::KEY_KEY_3:     strw = ("3"); break;
      case irr::KEY_KEY_4:     strw = ("4"); break;
      case irr::KEY_KEY_5:     strw = ("5"); break;
      case irr::KEY_KEY_6:     strw = ("6"); break;
      case irr::KEY_KEY_7:     strw = ("7"); break;
      case irr::KEY_KEY_8:     strw = ("8"); break;
      case irr::KEY_KEY_9:     strw = ("9"); break;
      case irr::KEY_KEY_A:     strw = ("A"); break;
      case irr::KEY_KEY_B:     strw = ("B"); break;
      case irr::KEY_KEY_C:     strw = ("C"); break;
      case irr::KEY_KEY_D:     strw = ("D"); break;
      case irr::KEY_KEY_E:     strw = ("E"); break;
      case irr::KEY_KEY_F:     strw = ("F"); break;
      case irr::KEY_KEY_G:     strw = ("G"); break;
      case irr::KEY_KEY_H:     strw = ("H"); break;
      case irr::KEY_KEY_I:     strw = ("I"); break;
      case irr::KEY_KEY_J:     strw = ("J"); break;
      case irr::KEY_KEY_K:     strw = ("K"); break;
      case irr::KEY_KEY_L:     strw = ("L"); break;
      case irr::KEY_KEY_M:     strw = ("M"); break;
      case irr::KEY_KEY_N:     strw = ("N"); break;
      case irr::KEY_KEY_O:     strw = ("O"); break;
      case irr::KEY_KEY_P:     strw = ("P"); break;
      case irr::KEY_KEY_Q:     strw = ("Q"); break;
      case irr::KEY_KEY_R:     strw = ("R"); break;
      case irr::KEY_KEY_S:     strw = ("S"); break;
      case irr::KEY_KEY_T:     strw = ("T"); break;
      case irr::KEY_KEY_U:     strw = ("U"); break;
      case irr::KEY_KEY_V:     strw = ("V"); break;
      case irr::KEY_KEY_W:     strw = ("W"); break;
      case irr::KEY_KEY_X:     strw = ("X"); break;
      case irr::KEY_KEY_Y:     strw = ("Y"); break;
      case irr::KEY_KEY_Z:     strw = ("Z"); break;
      case irr::KEY_LWIN:      strw = ("Left Windows"); break;
      case irr::KEY_RWIN:      strw = ("Right Windows"); break;
      case irr::KEY_APPS:      strw = ("Applications"); break;
      case irr::KEY_SLEEP:     strw = ("Sleep"); break;
      case irr::KEY_NUMPAD0:   strw = ("Num 0"); break;
      case irr::KEY_NUMPAD1:   strw = ("Num 1"); break;
      case irr::KEY_NUMPAD2:   strw = ("Num 2"); break;
      case irr::KEY_NUMPAD3:   strw = ("Num 3"); break;
      case irr::KEY_NUMPAD4:   strw = ("Num 4"); break;
      case irr::KEY_NUMPAD5:   strw = ("Num 5"); break;
      case irr::KEY_NUMPAD6:   strw = ("Num 6"); break;
      case irr::KEY_NUMPAD7:   strw = ("Num 7"); break;
      case irr::KEY_NUMPAD8:   strw = ("Num 8"); break;
      case irr::KEY_NUMPAD9:   strw = ("Num 9"); break;
      case irr::KEY_MULTIPLY:  strw = ("Multiply"); break;
      case irr::KEY_ADD:       strw = ("Add"); break;
      case irr::KEY_SEPARATOR: strw = ("Separator"); break;
      case irr::KEY_SUBTRACT:  strw = ("Subtract"); break;
      case irr::KEY_DECIMAL:   strw = ("Decimal"); break;
      case irr::KEY_DIVIDE:    strw = ("Divide"); break;
      case irr::KEY_F1:        strw = ("F1"); break;
      case irr::KEY_F2:        strw = ("F2"); break;
      case irr::KEY_F3:        strw = ("F3"); break;
      case irr::KEY_F4:        strw = ("F4"); break;
      case irr::KEY_F5:        strw = ("F5"); break;
      case irr::KEY_F6:        strw = ("F6"); break;
      case irr::KEY_F7:        strw = ("F7"); break;
      case irr::KEY_F8:        strw = ("F8"); break;
      case irr::KEY_F9:        strw = ("F9"); break;
      case irr::KEY_F10:       strw = ("F10"); break;
      case irr::KEY_F11:       strw = ("F11"); break;
      case irr::KEY_F12:       strw = ("F12"); break;
      case irr::KEY_NUMLOCK:   strw = ("NUM LOCK"); break;
      case irr::KEY_SCROLL:    strw = ("SCROLL LOCK"); break;
      case irr::KEY_LSHIFT:    strw = ("Left SHIFT"); break;
      case irr::KEY_RSHIFT:    strw = ("Right SHIFT"); break;
      case irr::KEY_LCONTROL:  strw = ("Left CONTROL"); break;
      case irr::KEY_RCONTROL:  strw = ("Right CONTROL"); break;
      case irr::KEY_LMENU:     strw = ("Left MENU"); break;
      case irr::KEY_RMENU:     strw = ("Right MENU"); break;
      case irr::KEY_COMMA:     strw = (","); break;
      case irr::KEY_PLUS:      strw = ("+"); break;
      case irr::KEY_MINUS:     strw = ("-"); break;
      case irr::KEY_PERIOD:    strw = ("."); break;
      case irr::KEY_ATTN:      strw = ("Attn"); break;
      case irr::KEY_CRSEL:     strw = ("CrSel"); break;
      case irr::KEY_EXSEL:     strw = ("ExSel"); break;
      case irr::KEY_EREOF:     strw = ("Erase EOF"); break;
      case irr::KEY_PLAY:      strw = ("Play"); break;
      case irr::KEY_ZOOM:      strw = ("Zoom"); break;
      case irr::KEY_PA1:       strw = ("PA1"); break;
      case irr::KEY_OEM_CLEAR: strw = ("Clear"); break;
      default:
	strw = ("UNKNOWN"); break;
    }
  return (strw);
}
