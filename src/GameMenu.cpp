//
// greg
//

#include "GameMenu.hpp"

namespace is
{
    GameMenu::GameMenu()
    {
    }
    GameMenu::~GameMenu()
    {
    }
    void GameMenu::Init(std::shared_ptr<GameEngine> engine)
    {
        _engine = engine;
    }
    void GameMenu::Cleanup(void)
    {
    }
    void GameMenu::Pause(void)
    {
    }
    void GameMenu::Resume(void)
    {

    }
    void GameMenu::HandleEvents(void)
    {
    }
    void GameMenu::Update(void)
    {
    }
    void GameMenu::Draw(void)
    {
    }
    void GameMenu::ChangeState(std::shared_ptr<GameEngine> engine, std::shared_ptr<IGameState> state)
    {
    }
}