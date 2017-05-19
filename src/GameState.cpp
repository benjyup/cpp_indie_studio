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

void is::GameState::Init(GameEngine *game)
{

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

void is::GameState::HandleEvents(is::GameEngine *game)
{

}

void is::GameState::Update(is::GameEngine *game)
{

}

void is::GameState::Draw(is::GameEngine *game)
{
  game->getDriver()->beginScene(true, true, irr::video::SColor(255, 255, 0, 0));
  game->getDriver()->endScene();
}

void is::GameState::ChangeState(is::GameEngine *game, is::IGameState *state)
{

}
