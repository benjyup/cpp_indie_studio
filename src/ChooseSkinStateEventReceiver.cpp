//
// Created by vincent on 18/06/17.
//

#include <Button.hpp>
#include <iostream>
#include "ChooseSkinStateEventReceiver.hpp"

is::ChooseSkinStateEventReceiver::ChooseSkinStateEventReceiver()
{

}

is::ChooseSkinStateEventReceiver::~ChooseSkinStateEventReceiver()
{

}

void is::ChooseSkinStateEventReceiver::init(SContext *context)
{
  this->_context = context;
}

bool is::ChooseSkinStateEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
    {
      irr::s32	buttonID = event.GUIEvent.Caller->getID();
      switch (buttonID)
	{
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_UP_ARROW):
	    this->_nextTexture();
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_DOWN_ARROW):
	    this->_prevTexture();
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_LEFT_ARROW):
	    this->_prevMesh();
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_RIGHT_ARROW):
	    this->_nextMesh();
	  break;
	  case ((irr::s32)Button::GUI_ID_BOUTON::GUI_ID_SKIN_APPLY):
	    this->_apply();
	  break;
	  default:
		break;
	}
    }
  return false;
}

void is::ChooseSkinStateEventReceiver::_nextMesh()
{
  this->_context->current_index = (this->_context->current_index + 1) % this->_context->meshes->size();
}

void is::ChooseSkinStateEventReceiver::_prevMesh()
{
  if (this->_context->current_index == 0)
    {
      this->_context->current_index = this->_context->meshes->size() - 1;
    }
  else
    this->_context->current_index -= 1;
}

void is::ChooseSkinStateEventReceiver::_nextTexture()
{

}

void is::ChooseSkinStateEventReceiver::_prevTexture()
{

}

void is::ChooseSkinStateEventReceiver::_apply()
{
  this->_context->apply = true;
}

