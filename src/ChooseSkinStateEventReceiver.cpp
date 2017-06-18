//
// Created by vincent on 18/06/17.
//

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
  return false;
}
