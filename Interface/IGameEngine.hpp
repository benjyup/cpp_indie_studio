//
// Created by jeanadrien on 09/05/17.
//

#ifndef CPP_INDIE_STUDIO_IGAMEENGINE_HPP
#define CPP_INDIE_STUDIO_IGAMEENGINE_HPP

# include "IGameState.hpp"


namespace is {
	class IGameState;
	class IGameEngine {
	public:
		virtual ~IGameEngine() {}

		virtual void ChangeState(std::shared_ptr<IGameState> state) = 0;

		virtual void PushState(std::shared_ptr<IGameState> state) = 0;

		virtual void PopState(void) = 0;

		virtual void HandleEvents(void) = 0;

		virtual void Update(void) = 0;

		virtual void Draw(void) = 0;

		virtual void Quit(void) = 0;

		virtual bool Running(void) = 0;

	 protected:
	  virtual void Init(const char *title, int width = 640, int height = 480,
			    int bpp = 0, bool fullscreen = false) = 0;

	  virtual void Cleanup() = 0;
	};
}

#endif //CPP_INDIE_STUDIO_IGAMEENGINE_HPP
