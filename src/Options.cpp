//
// Created by vincent on 19/05/17.
//

#include "Options.hpp"
#include "IndieStudioException.hpp"

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
	{is::Options::MOVES::MOVE_ACTION, irr::KEY_RCONTROL},
	{is::Options::MOVES::MOVE_UP, irr::KEY_UP},
	{is::Options::MOVES::MOVE_DOWN, irr::KEY_DOWN},
	{is::Options::MOVES::MOVE_RIGHT, irr::KEY_RIGHT},
	{is::Options::MOVES::MOVE_LEFT, irr::KEY_LEFT}
};

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
  if (this->isAlreadyBind(1, key, move))
    {
      irr::core::string<char> s(this->keyToString<irr::core::stringw>(key));
      throw is::IndieStudioException(std::string(s.c_str()) + " is already bind.");
    }
  this->_p1Config[move] = key ;
}

void is::Options::setP2config(const irr::EKEY_CODE key, const is::Options::MOVES move)
{
  if (this->isAlreadyBind(2, key, move))
    {
      irr::core::string<char> s(this->keyToString<irr::core::stringw>(key));
      throw is::IndieStudioException(std::string(s.c_str()) + " is already bind.");
    }
  this->_p2Config[move] = key ;
}

void is::Options::setP1config(const std::map<is::Options::MOVES, irr::EKEY_CODE> &moves)
{
  for (auto move : moves)
    this->setP1config(move.second, move.first);
}

void is::Options::setP2config(const std::map<is::Options::MOVES , irr::EKEY_CODE> &moves)
{
  for (auto move : moves)
    this->setP2config(move.second, move.first);
}

bool 		is::Options::isAlreadyBind(int player, const irr::EKEY_CODE key, const Options::MOVES move) const
{
  auto		checkedPlayer = (player == 1) ? (this->_p1Config.begin()) : (this->_p2Config.begin());
  auto		secondPlayer = (player == 1) ? (this->_p2Config.begin()) : (this->_p1Config.begin());

  for (const auto &it : this->_p1Config)
    {
      if ((checkedPlayer->first != move && checkedPlayer->second == key) ||
	      secondPlayer->second == key)
	return (true);
      ++checkedPlayer;
      ++secondPlayer;
    }
  return (false);
}

std::vector<is::Player> &is::Options::getPlayers()
{
  return _players;
}

void is::Options::setPlayers(const std::vector<is::Player> &players)
{
  this->_players = players;
}

template <typename T>
T is::Options::keyToString(irr::EKEY_CODE key) const
{
  T str;

  switch (key)
    {
      case irr::KEY_CANCEL:    str = ("CANCEL"); break;
      case irr::KEY_BACK:      str = ("BACKSPACE"); break;
      case irr::KEY_TAB:       str = ("TAB"); break;
      case irr::KEY_CLEAR:     str = ("CLEAR"); break;
      case irr::KEY_RETURN:    str = ("ENTER"); break;
      case irr::KEY_SHIFT:     str = ("SHIFT"); break;
      case irr::KEY_CONTROL:   str = ("CTRL"); break;
      case irr::KEY_MENU:      str = ("ALT"); break;
      case irr::KEY_PAUSE:     str = ("PAUSE"); break;
      case irr::KEY_CAPITAL:   str = ("CAPS LOCK"); break;
      case irr::KEY_ESCAPE:    str = ("ESC"); break;
      case irr::KEY_SPACE:     str = ("SPACEBAR"); break;
      case irr::KEY_PRIOR:     str = ("PAGE UP"); break;
      case irr::KEY_NEXT:      str = ("PAGE DOWN"); break;
      case irr::KEY_END:       str = ("END"); break;
      case irr::KEY_HOME:      str = ("HOME"); break;
      case irr::KEY_LEFT:      str = ("LEFT ARROW"); break;
      case irr::KEY_UP:        str = ("UP ARROW"); break;
      case irr::KEY_RIGHT:     str = ("RIGHT ARROW"); break;
      case irr::KEY_DOWN:      str = ("DOWN ARROW"); break;
      case irr::KEY_SELECT:    str = ("SELECT"); break;
      case irr::KEY_PRINT:     str = ("PRINT"); break;
      case irr::KEY_EXECUT:    str = ("EXECUTE"); break;
      case irr::KEY_SNAPSHOT:  str = ("PRINT SCREEN"); break;
      case irr::KEY_INSERT:    str = ("INSERT"); break;
      case irr::KEY_DELETE:    str = ("DELETE"); break;
      case irr::KEY_HELP:      str = ("HELP"); break;
      case irr::KEY_KEY_0:     str = ("0"); break;
      case irr::KEY_KEY_1:     str = ("1"); break;
      case irr::KEY_KEY_2:     str = ("2"); break;
      case irr::KEY_KEY_3:     str = ("3"); break;
      case irr::KEY_KEY_4:     str = ("4"); break;
      case irr::KEY_KEY_5:     str = ("5"); break;
      case irr::KEY_KEY_6:     str = ("6"); break;
      case irr::KEY_KEY_7:     str = ("7"); break;
      case irr::KEY_KEY_8:     str = ("8"); break;
      case irr::KEY_KEY_9:     str = ("9"); break;
      case irr::KEY_KEY_A:     str = ("A"); break;
      case irr::KEY_KEY_B:     str = ("B"); break;
      case irr::KEY_KEY_C:     str = ("C"); break;
      case irr::KEY_KEY_D:     str = ("D"); break;
      case irr::KEY_KEY_E:     str = ("E"); break;
      case irr::KEY_KEY_F:     str = ("F"); break;
      case irr::KEY_KEY_G:     str = ("G"); break;
      case irr::KEY_KEY_H:     str = ("H"); break;
      case irr::KEY_KEY_I:     str = ("I"); break;
      case irr::KEY_KEY_J:     str = ("J"); break;
      case irr::KEY_KEY_K:     str = ("K"); break;
      case irr::KEY_KEY_L:     str = ("L"); break;
      case irr::KEY_KEY_M:     str = ("M"); break;
      case irr::KEY_KEY_N:     str = ("N"); break;
      case irr::KEY_KEY_O:     str = ("O"); break;
      case irr::KEY_KEY_P:     str = ("P"); break;
      case irr::KEY_KEY_Q:     str = ("Q"); break;
      case irr::KEY_KEY_R:     str = ("R"); break;
      case irr::KEY_KEY_S:     str = ("S"); break;
      case irr::KEY_KEY_T:     str = ("T"); break;
      case irr::KEY_KEY_U:     str = ("U"); break;
      case irr::KEY_KEY_V:     str = ("V"); break;
      case irr::KEY_KEY_W:     str = ("W"); break;
      case irr::KEY_KEY_X:     str = ("X"); break;
      case irr::KEY_KEY_Y:     str = ("Y"); break;
      case irr::KEY_KEY_Z:     str = ("Z"); break;
      case irr::KEY_LWIN:      str = ("Left Windows"); break;
      case irr::KEY_RWIN:      str = ("Right Windows"); break;
      case irr::KEY_APPS:      str = ("Applications"); break;
      case irr::KEY_SLEEP:     str = ("Sleep"); break;
      case irr::KEY_NUMPAD0:   str = ("Num 0"); break;
      case irr::KEY_NUMPAD1:   str = ("Num 1"); break;
      case irr::KEY_NUMPAD2:   str = ("Num 2"); break;
      case irr::KEY_NUMPAD3:   str = ("Num 3"); break;
      case irr::KEY_NUMPAD4:   str = ("Num 4"); break;
      case irr::KEY_NUMPAD5:   str = ("Num 5"); break;
      case irr::KEY_NUMPAD6:   str = ("Num 6"); break;
      case irr::KEY_NUMPAD7:   str = ("Num 7"); break;
      case irr::KEY_NUMPAD8:   str = ("Num 8"); break;
      case irr::KEY_NUMPAD9:   str = ("Num 9"); break;
      case irr::KEY_MULTIPLY:  str = ("Multiply"); break;
      case irr::KEY_ADD:       str = ("Add"); break;
      case irr::KEY_SEPARATOR: str = ("Separator"); break;
      case irr::KEY_SUBTRACT:  str = ("Subtract"); break;
      case irr::KEY_DECIMAL:   str = ("Decimal"); break;
      case irr::KEY_DIVIDE:    str = ("Divide"); break;
      case irr::KEY_F1:        str = ("F1"); break;
      case irr::KEY_F2:        str = ("F2"); break;
      case irr::KEY_F3:        str = ("F3"); break;
      case irr::KEY_F4:        str = ("F4"); break;
      case irr::KEY_F5:        str = ("F5"); break;
      case irr::KEY_F6:        str = ("F6"); break;
      case irr::KEY_F7:        str = ("F7"); break;
      case irr::KEY_F8:        str = ("F8"); break;
      case irr::KEY_F9:        str = ("F9"); break;
      case irr::KEY_F10:       str = ("F10"); break;
      case irr::KEY_F11:       str = ("F11"); break;
      case irr::KEY_F12:       str = ("F12"); break;
      case irr::KEY_NUMLOCK:   str = ("NUM LOCK"); break;
      case irr::KEY_SCROLL:    str = ("SCROLL LOCK"); break;
      case irr::KEY_LSHIFT:    str = ("Left SHIFT"); break;
      case irr::KEY_RSHIFT:    str = ("Right SHIFT"); break;
      case irr::KEY_LCONTROL:  str = ("Left CONTROL"); break;
      case irr::KEY_RCONTROL:  str = ("Right CONTROL"); break;
      case irr::KEY_LMENU:     str = ("Left MENU"); break;
      case irr::KEY_RMENU:     str = ("Right MENU"); break;
      case irr::KEY_COMMA:     str = (","); break;
      case irr::KEY_PLUS:      str = ("+"); break;
      case irr::KEY_MINUS:     str = ("-"); break;
      case irr::KEY_PERIOD:    str = ("."); break;
      case irr::KEY_ATTN:      str = ("Attn"); break;
      case irr::KEY_CRSEL:     str = ("CrSel"); break;
      case irr::KEY_EXSEL:     str = ("ExSel"); break;
      case irr::KEY_EREOF:     str = ("Erase EOF"); break;
      case irr::KEY_PLAY:      str = ("Play"); break;
      case irr::KEY_ZOOM:      str = ("Zoom"); break;
      case irr::KEY_PA1:       str = ("PA1"); break;
      case irr::KEY_OEM_CLEAR: str = ("Clear"); break;
      default:
	str = ("UNKNOWN"); break;
    }
  return (str);
}
