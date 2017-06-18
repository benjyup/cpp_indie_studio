//
// Created by vincent on 17/06/17.
//

#ifndef CPP_INDIE_STUDIO_CHOOSEPLAYEREVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_CHOOSEPLAYEREVENTRECEIVER_HPP

#include <array>
#include "irrlicht.h"
#include "Button.hpp"
#include "Options.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"


namespace is
{

class ChoosePlayerEventReceiver : public irr::IEventReceiver
{
 public:
  struct SContext
  {
    GameEngine 					*engine;
    std::vector<is::Button> 			*buttons;
    std::vector<Player>				*players;
    std::array<std::pair<irr::video::ITexture *, irr::video::ITexture *>, 4>	*gfxAI;
    std::array<std::pair<irr::video::ITexture *, irr::video::ITexture *>, 2>	*gfxPlayer;
    irr::u32					nbrOfPlayers;
    irr::u32					nbrOfAI;
    bool 					stop;
  };

  ChoosePlayerEventReceiver();
  ~ChoosePlayerEventReceiver();

  void						init(SContext *sContext);
  virtual bool 					OnEvent(const irr::SEvent& event);

 private:
  std::array<std::pair<Player::PlayerType, std::string>,
	  4>					_players;
  SContext					*_sContext;

  void 						_addPlayer(Player::PlayerType type, irr::u32 &nbrOf);
  void 						_deletePlayer(Player::PlayerType type, irr::u32 &nbrOf);
};

}

#endif //CPP_INDIE_STUDIO_CHOOSEPLAYEREVENTRECEIVER_HPP
