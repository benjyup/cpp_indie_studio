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

  void					setMenuMode();
  void					setInGameMode();
  void					setSplashScreen();

  void 					setAnimation1();
  void 					setAnimation2();
  void 					setAnimation3();
  void 					setAnimation4();

  irr::scene::ISceneManager 		*get_smgr() const;

  CamMode 				get_currMode() const;

  void 					set_smgr(irr::scene::ISceneManager *_smgr);

  void 					set_currMode(CamMode _currMode);

 private:
  irr::scene::ISceneManager*		_smgr;
  CamMode 				_currMode;
  is::GameEngine			*_engine;
  irr::ITimer 				*_timer;
  irr::scene::ICameraSceneNode		*_camera;
  irr::scene::ISceneNodeAnimator	*_anim = 0;
  irr::u32 				_anim1Time;
  irr::u32 				_anim2Time;
  irr::u32 				_anim3Time;
  irr::u32 				_anim4Time;
};

#endif //MAP_CAMERA_HPP
