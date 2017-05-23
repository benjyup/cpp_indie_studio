//
// Created by vincent on 11/05/17.
//

#include "GameState.hpp"

is::GameState::GameState(void)
{

}

is::GameState::~GameState(void)
{

}

void is::GameState::Init(GameEngine *engine)
{
  _engine = engine;
}

void is::GameState::Cleanup(void)
{

}

void is::GameState::Pause(void)
{

}

void is::GameState::Resume(void)
{

}

void is::GameState::HandleEvents(void)
{

}

void is::GameState::Update(void)
{

}

void is::GameState::Draw()
{
  _engine->getDriver()->beginScene(true, true, irr::video::SColor(255, 255, 0, 0));
  _engine->getDriver()->endScene();
}

void is::GameState::ChangeState(is::GameEngine *game,
				is::IGameState *state)
{

}
