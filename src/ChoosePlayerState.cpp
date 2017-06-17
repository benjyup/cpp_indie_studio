//
// Created by vincent on 17/06/17.
//

#include "ChoosePlayerState.hpp"

is::ChoosePlayerState::ChoosePlayerState() :
	_buttons()
{

}

is::ChoosePlayerState::~ChoosePlayerState()
{

}

void is::ChoosePlayerState::Init(is::GameEngine *engine)
{
  engine->getSceneManager()->createNewSceneManager();
  this->_options = &engine->getOptions();
  this->_gui = engine->getGuiEnv();
  this->_driver = engine->getDriver();

  this->_buttons.emplace_back(0, 0, 10, 10, 0, L"COUCOU", L"");
}

void is::ChoosePlayerState::Cleanup(void)
{

}

void is::ChoosePlayerState::Pause(void)
{

}

void is::ChoosePlayerState::Resume(void)
{

}

void is::ChoosePlayerState::HandleEvents(void)
{

}

void is::ChoosePlayerState::Update(void)
{

}

void is::ChoosePlayerState::Draw(void)
{
  this->_driver->beginScene();
  this->_buttons[0]->draw();
  this->_driver->endScene();
}

void is::ChoosePlayerState::ChangeState(is::GameEngine *engine, is::IGameState *state)
{

}
