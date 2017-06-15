//
// Created by vincent on 23/05/17.
//

#include <iostream>
#include <unistd.h>
#include "OptionsEventReceiver.hpp"
#include "IndieStudioException.hpp"

const irr::core::stringw			is::OptionsEventReceiver::PRESS_KEY = L"PRESS KEY";

is::OptionsEventReceiver::OptionsEventReceiver() : _getKey(false), _keyToChange()
{

}

is::OptionsEventReceiver::~OptionsEventReceiver()
{

}

bool is::OptionsEventReceiver::OnEvent(const irr::SEvent &event)
{

  switch(event.EventType)
    {
      case irr::EET_GUI_EVENT:
					this->_guiEvent(event);
      		break;
      case irr::EET_KEY_INPUT_EVENT:
					this->_keyEvent(event);
      		break;
    }
  return (false);
}

void is::OptionsEventReceiver::_guiEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
    {
      irr::s32	buttonID = event.GUIEvent.Caller->getID();
      switch (buttonID)
	{
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_CHANGE_PLAYER_BUTTON):
	    {
	      this->_optionsContext->player = (this->_optionsContext->player == 1) ? (2) : (1);
				this->_optionsContext->name = std::string("Player " + std::to_string(this->_optionsContext->player));
				this->_optionsContext->buttons->back()->setText(irr::core::stringw(this->_optionsContext->name.c_str()).c_str());
				this->_refresh();
	      this->_getKey = false;
	    }
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_CANCEL_BUTTON):
	    {
	      this->_getKey = false;
	      this->_optionsContext->engine->PopState();
	    }
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_APPLY_BUTTON):
	    {
	      this->_getKey = false;
	      try {
		  	this->_optionsContext->engine->getOptions().setP1config(this->_optionsContext->player1ConfigTmp);
		  	this->_optionsContext->engine->getOptions().setP2config(this->_optionsContext->player2ConfigTmp);
						} catch (const is::IndieStudioException &e) {
								this->_optionsContext->errorMsg->setText(irr::core::stringw(e.what()).c_str());
		  					return ;
								}
	    	this->_optionsContext->engine->PopState();
	    	}
	  break;
		case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_ACTION_BUTTON):
	  break;
		case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_FORWARD_BUTTON):
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_BACKWARD_BUTTON):
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_RIGHT_BUTTON):
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_TMP_MOVE_LEFT_BUTTON):
	  break;
	  default:
	    {
				event.GUIEvent.Caller->setID((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_PRESS_BUTTON);
				this->_getKey = true;
	      this->_keyToChange = Button::GUI_ID_BOUTON(buttonID);
				}
	}
    }
}

void is::OptionsEventReceiver::_keyEvent(const irr::SEvent &event)
{
  if (event.KeyInput.Key == irr::KEY_ESCAPE)
    this->_optionsContext->engine->Quit();
  try {
      if (this->_getKey)
	{
	  this->_getPlayerConfig(this->_optionsContext->player)[Button::BUTTON_TO_MOVE.at(this->_keyToChange)] = event.KeyInput.Key;
	  this->_refresh();
	  this->_getKey = false;
	}
    } catch (...) { }
}

void is::OptionsEventReceiver::Init(SOptionsContext *optionsContext)
{
  this->_optionsContext = optionsContext;
  this->_initConfig();
}

void is::OptionsEventReceiver::_initConfig(void)
{
  this->_optionsContext->player1ConfigTmp = this->_optionsContext->engine->getOptions().getP1Config();
  this->_optionsContext->player2ConfigTmp = this->_optionsContext->engine->getOptions().getP2Config();
}

std::map<is::Options::MOVES, irr::EKEY_CODE> &is::OptionsEventReceiver::_getPlayerConfig(irr::s8 player)
{
  if (player == 1)
    return (this->_optionsContext->player1ConfigTmp);
  else
    return (this->_optionsContext->player2ConfigTmp);
}

void is::OptionsEventReceiver::_refresh()
{
  auto &playerConfig = this->_getPlayerConfig(this->_optionsContext->player);
  auto it = playerConfig.begin();

  for (auto i = 0 ; i < 5 ; i++)
    {
      (*(this->_optionsContext->buttons))[i]->setText(this->_optionsContext->engine->getOptions().keyToString<irr::core::stringw>(it->second).c_str());
      ++it;
    }
}
