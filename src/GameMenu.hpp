//
// greg
//

#include "IGameState.hpp"
#include "GameEngine.hpp"

namespace is 
{
    class GameMenu : public IGameState
    {
        private:
            std::shared_ptr<GameEngine> _engine;
        public:
            GameMenu();
            virtual ~GameMenu();
            virtual void Init(std::shared_ptr<GameEngine> engine);
            virtual void Cleanup(void);
            virtual void Pause(void);
            virtual void Resume(void);
            virtual void HandleEvents(void);
            virtual void Update(void);
            virtual void Draw(void);
            virtual void ChangeState(std::shared_ptr<GameEngine> engine, std::shared_ptr<IGameState> state);        
    }; 
}