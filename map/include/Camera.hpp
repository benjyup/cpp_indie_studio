//
// Created by peixot_b on 12/06/17.
//

#ifndef MAP_CAMERA_HPP
#define MAP_CAMERA_HPP


#include <irrlicht.h>
#include "../../src/GameEngine.hpp"

enum	CamMode
{
  MENU = 0,
  INGAME,
  SPLASHSCREEN
};

class Camera
{
 public:
  Camera(irr::scene::ISceneManager* smgr, CamMode cameraMode, is::GameEngine *engine);
  virtual ~Camera();

  void				setMenuMode();
  void				setInGameMode();
  void				setSplashScreen();

  irr::scene::ISceneManager *get_smgr() const;

  CamMode get_currMode() const;

  void set_smgr(irr::scene::ISceneManager *_smgr);

  void set_currMode(CamMode _currMode);

 private:
  irr::scene::ISceneManager*	_smgr;
  CamMode 			_currMode;
  is::GameEngine		*_engine;
  irr::ITimer 			*_timer;
};

#endif //MAP_CAMERA_HPP
