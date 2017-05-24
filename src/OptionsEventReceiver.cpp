//
// Created by vincent on 23/05/17.
//

#include "OptionsEventReceiver.hpp"

is::OptionsEventReceiver::OptionsEventReceiver()
{

}

is::OptionsEventReceiver::~OptionsEventReceiver()
{

}

bool is::OptionsEventReceiver::OnEvent(const irr::SEvent &event)
{
  return (false);
}

void is::OptionsEventReceiver::Init(SOptionsContext *optionsContext)
{
  this->_optionsContext = optionsContext;
}
