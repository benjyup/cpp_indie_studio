//
// Created by vincent on 17/06/17.
//

#include <iostream>
#include "ChoosePlayerEventReceiver.hpp"

is::ChoosePlayerEventReceiver::ChoosePlayerEventReceiver()
{

}

is::ChoosePlayerEventReceiver::~ChoosePlayerEventReceiver()
{

}

bool is::ChoosePlayerEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
    {
      irr::s32	buttonID = event.GUIEvent.Caller->getID();
      switch (buttonID)
	{
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_PLAYER):
	    _addPlayer(Player::PLAYER, this->_sContext->nbrOfPlayers);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_AI):
	    _addPlayer(Player::AI, this->_sContext->nbrOfAI);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_PLAY):
	    _play();
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_DELETE_PLAYER):
	    this->_deletePlayer(Player::PLAYER, this->_sContext->nbrOfPlayers);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_DELETE_AI):
	    this->_deletePlayer(Player::AI, this->_sContext->nbrOfAI);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS1):
	    this->_chooseSkin(0);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS2):
	    this->_chooseSkin(1);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS3):
	    this->_chooseSkin(2);
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS4):
	    this->_chooseSkin(3);
	  break;
	}
    }
  return false;
}


void is::ChoosePlayerEventReceiver::init(is::ChoosePlayerEventReceiver::SContext *sContext)
{
  this->_sContext = sContext;
}

void is::ChoosePlayerEventReceiver::_deletePlayer(Player::PlayerType playerType, irr::u32 &nbrOf)
{
  if (nbrOf <= 0)
    return ;

  irr::u32		i = this->_sContext->players->size() - 1;
  while (i >= 0 &&  this->_sContext->players->at(i).getType() != playerType)
    i -= 1;
  this->_sContext->players->at(i).setType(Player::PlayerType::VOID);
  nbrOf -= 1;
}

void is::ChoosePlayerEventReceiver::_addPlayer(is::Player::PlayerType playerType, irr::u32 &nbrOf)
{
  irr::u32 		i = 0;

  if (nbrOf >= ((playerType == Player::AI) ? (1) : (2)))
    return ;

  while (i < this->_sContext->players->size() && this->_sContext->players->at(i).getType() != Player::VOID)
    i += 1;
  if (i != this->_sContext->players->size())
    {
      this->_sContext->players->at(i).setType(playerType);
      nbrOf += 1;
    }
}

void is::ChoosePlayerEventReceiver::_chooseSkin(int pos)
{
  std::cerr << "chooseSkin" << std::endl;
  if (this->_sContext->players->at(pos).getType() != Player::PlayerType::VOID)
    {
      std::cerr << "chooseSkin" << std::endl;
      this->_sContext->chooseSkin = true;
      this->_sContext->player = pos;
    }
}

void is::ChoosePlayerEventReceiver::_play()
{
  int 		playerFound = 0;

  for (auto &p : *(this->_sContext->players))
    {
      if (p.getType() != Player::PlayerType::VOID)
	playerFound += 1;
      if (p.getType() != Player::PlayerType::VOID && (p.getMeshPath().empty() || p.getTexturePath().empty()))
	{
	  std::cout << p.getMeshPath() << " " << p.getTexturePath() << std::endl;
	  std::cerr << "RETURN" << std::endl;
	  return ;
	}
    }
  std::cerr << "TRUE" << std::endl;
  if (playerFound >= 2)
    this->_sContext->stop = true;
}
