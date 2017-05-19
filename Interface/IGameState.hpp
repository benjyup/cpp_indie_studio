//
// Created by vincent on 09/05/17.
//

#ifndef CPP_INDIE_STUDIO_IGAMESTATE_HPP
# define CPP_INDIE_STUDIO_IGAMESTATE_HPP

#include "../src/GameEngine.hpp"

namespace is {
	class GameEngine;
	class IGameState {

	public:
		virtual ~IGameState() {}

		virtual void Init(GameEngine *game) = 0;

		virtual void Cleanup(void) = 0;

		virtual void Pause(void) = 0;

		virtual void Resume(void) = 0;

		virtual void HandleEvents(GameEngine *game) = 0;

		virtual void Update(GameEngine *game) = 0;

		virtual void Draw(GameEngine *game) = 0;

		virtual void ChangeState(GameEngine *game, IGameState *state) = 0;
	};
}

#endif //CPP_INDIE_STUDIO_IGAMESTATE_HPP
