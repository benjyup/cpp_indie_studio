//
// Created by vincent on 09/05/17.
//

#ifndef CPP_INDIE_STUDIO_IGAMESTATE_HPP
# define CPP_INDIE_STUDIO_IGAMESTATE_HPP

#include <memory>
#include "../src/GameEngine.hpp"

namespace is {
	class GameEngine;
	class IGameState {

	public:
		virtual ~IGameState() {}

		virtual void Init(std::shared_ptr<GameEngine> engine) = 0;

		virtual void Cleanup(void) = 0;

		virtual void Pause(void) = 0;

		virtual void Resume(void) = 0;

		virtual void HandleEvents(void) = 0;

		virtual void Update(void) = 0;

		virtual void Draw(void) = 0;

		virtual void ChangeState(std::shared_ptr<GameEngine> engine, std::shared_ptr<IGameState> state) = 0;
	};
}

#endif //CPP_INDIE_STUDIO_IGAMESTATE_HPP
