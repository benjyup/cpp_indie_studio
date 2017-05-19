//
// Created by vincent on 19/05/17.
//

#include "Options.hpp"

const irr::u8 						is::Options::DEFAULT_VOLUME = 25;
const bool 						is::Options::DEFAULT_FULLSCREEN = false;
const std::map<is::Options::MOVES, irr::EKEY_CODE>	is::Options::DEFAULT_P1_CONFIG = {
	{is::Options::MOVES::MOVE_UP, irr::KEY_KEY_Z},
	{is::Options::MOVES::MOVE_DOWN, irr::KEY_KEY_S},
	{is::Options::MOVES::MOVE_RIGHT, irr::KEY_KEY_D},
	{is::Options::MOVES::MOVE_LEFT, irr::KEY_KEY_Q}
};
const std::map<is::Options::MOVES, irr::EKEY_CODE>	is::Options::DEFAULT_P2_CONFIG = {
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

void is::Options::setVolume(irr::u8 pourcent)
{
  this->_volume = pourcent;
}

void is::Options::setP1config(irr::EKEY_CODE key, is::Options::MOVES move)
{
  this->_p1Config[move] = key ;
}

void is::Options::setP2config(irr::EKEY_CODE key, is::Options::MOVES move)
{
  this->_p2Config[move] = key ;
}
