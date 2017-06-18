//
// Created by kyxo on 5/24/17.
//

#ifndef CPP_INDIE_STUDIO_GAME_HPP
#define CPP_INDIE_STUDIO_GAME_HPP


#pragma once

#include <vector>
#include <iostream>
#include <mutex>
#include "BombsManager.hpp"
#include "IGameState.hpp"
#include "GameEventReceiver.hpp"
#include "map.hpp"
#include "ParseMap.hpp"
#include "BombsManager.hpp"
#include "PowerUpManager.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "GenerateMap.hpp"
#include "Button.hpp"

namespace is
{
  class GameState : public IGameState
  {
   public:

    GameState();
    virtual ~GameState();
    virtual void Init(GameEngine *engine);
    virtual void Cleanup(void);
    virtual void Pause(void);
    virtual void Resume(void);
    virtual void HandleEvents(void);
    virtual void Update(void);
    virtual void Draw(void);
    virtual void ChangeState(GameEngine *engine,
			     IGameState *state);
   private:
   void          addText();
    void	checkWinner();
   void          addButtons();
   void          setTime();
    CHANGE 					_change;
    ParseMap	    				_parserMap;
    GenerateMap					_genMap;
    irr::video::IVideoDriver			*_driver;
    irr::scene::ISceneManager			*_sceneManager;
    irr::gui::IGUIEnvironment			*_gui;
    GameEngine 					*_engine;
    std::shared_ptr<map>			_map;
    std::shared_ptr<BombsManager>		_bombs;
    std::list<std::shared_ptr<Character>>	_char;
    std::shared_ptr<is::PowerUpManager>       _powManager;

    Options					*_opt;
    GameEventReceiver				_receiver;
    std::shared_ptr<Camera>			_cam;
    bool					changing;
    std::map<int, irr::gui::IGUIStaticText*> 	    _text;
    irr::gui::IGUIFont                          *_font;
    std::vector<is::Button> 			              _buttons;
    std::map<Button::GUI_ID_BOUTON, irr::video::ITexture*> _pathButton;
    int                                                 _baseTime;
    std::string                                            _time;
    int                                                    min;
   };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP
