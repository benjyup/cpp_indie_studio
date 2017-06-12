//
// Created by peixot_b on 12/06/17.
//

#ifndef MAP_CAMERA_HPP
#define MAP_CAMERA_HPP


#include <irrlicht.h>

enum	CamMode
{
  MENU = 0,
  INGAME,
  SPLASHSCREEN
};

class Camera
{
 public:
  Camera(irr::scene::ISceneManager* smgr, CamMode cameraMode);
  virtual ~Camera();

 private:
  irr::scene::ISceneManager* _smgr;
};

#endif //MAP_CAMERA_HPP
