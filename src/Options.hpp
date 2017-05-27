//
// Created by vincent on 19/05/17.
//

#pragma once
#include <unordered_map>
#include <Keycodes.h>
#include <vector>
#include <regex>
#include "irrlicht.h"

namespace is
{
  class Options
  {
   public:
    enum class MOVES : irr::u8
    {
      MOVE_ACTION = 0,
      MOVE_UP,
      MOVE_DOWN,
      MOVE_RIGHT,
      MOVE_LEFT,
      MOVE_LENGTH,
    };
    static const irr::u8					DEFAULT_VOLUME;
    static const bool 						DEFAULT_FULLSCREEN;
    static const std::map<Options::MOVES, irr::EKEY_CODE>	DEFAULT_P1_CONFIG;
    static const std::map<Options::MOVES, irr::EKEY_CODE>	DEFAULT_P2_CONFIG;

    Options();
    ~Options();

    const std::map<Options::MOVES, irr::EKEY_CODE>		&getP1Config() const;
    const std::map<Options::MOVES, irr::EKEY_CODE>		&getP2Config() const;
    irr::u8							getVolume() const;

    void							setVolume(const irr::u8 pourcent);
    void 							setP1config(const irr::EKEY_CODE key, const Options::MOVES move);
    void 							setP2config(const irr::EKEY_CODE key, const Options::MOVES move);
    void 							setP1config(const std::map<Options::MOVES, irr::EKEY_CODE> &moves);
    void 							setP2config(const std::map<Options::MOVES, irr::EKEY_CODE> &moves);

    template <typename T = std::string>
    T 								keyToString(irr::EKEY_CODE key) const;


   private:
    static const std::map<irr::EKEY_CODE, irr::core::stringw>	KEY_TO_WCHAR;

    irr::u8							_volume;
    bool 							_fullscreen;
    std::map<Options::MOVES, irr::EKEY_CODE> 			_p1Config;
    std::map<Options::MOVES, irr::EKEY_CODE> 			_p2Config;

    bool 							isAlreadyBind(int player, const irr::EKEY_CODE, const Options::MOVES move) const;
  };
}
