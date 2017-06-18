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
	    {
	      if (this->_sContext->nbrOfPlayers < 2)
		{
		  _addPlayer();
		  std::cerr << "ADD PLAYER" << std::endl;
		}
	    }
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_AI):
	    {
	      if (this->_sContext->nbrOfAI < 4)
		{
		  _addAI();
		  std::cerr << "ADD AI" << std::endl;
		}
	    }
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_PLAY):
	    {
	      this->_sContext->stop = true;
	    }
	  break;

	}
    }
  return false;
}


void is::ChoosePlayerEventReceiver::init(is::ChoosePlayerEventReceiver::SContext *sContext)
{
  this->_sContext = sContext;
}

void is::ChoosePlayerEventReceiver::_addPlayer()
{
  irr::u32 		i = 0;

  this->_sContext->nbrOfPlayers += 1;
  while (i < this->_sContext->players->size() && this->_sContext->players->at(i).getType() != Player::VOID)
    i += 1;
  std::cout << "i = " << i << std::endl;
  if (i != this->_sContext->players->size())
    {
      this->_sContext->players->at(i).setType(Player::PlayerType::PLAYER);
    }
}

void is::ChoosePlayerEventReceiver::_addAI()
{
  irr::u32 		i = 0;

  this->_sContext->nbrOfAI += 1;
  while (i < this->_sContext->players->size() && this->_sContext->players->at(i).getType() != Player::VOID)
    i += 1;
  std::cout << "i = " << i << std::endl;
  if (i != this->_sContext->players->size())
    {
      this->_sContext->players->at(i).setType(Player::PlayerType::AI);
    }
}
