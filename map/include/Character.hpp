//
// Created by kyxo on 5/30/17.
//

#ifndef CPP_INDIE_STUDIO_CHARACTER_HPP
#define CPP_INDIE_STUDIO_CHARACTER_HPP

#include <string>

using namespace irr;

#define DEFAULT_SPEED 30
#define DEFAULT_POWER 1
#define DEFAULT_BOMB 1

class Character
{
 public:
  Character(scene::IAnimatedMesh *node, video::ITexture *texture, scene::ISceneManager  * smgr,
	    	core::vector3df const & pos);
  ~Character() {}
 private:
  scene::IAnimatedMeshSceneNode	*_mesh;
  video::ITexture		*_text;
  scene::ISceneManager 		*_smgr;
  core::vector3df		_pos;
  int 				_speed;
  int 				_bomb;
  int 				_power;
};


#endif //CPP_INDIE_STUDIO_CHARACTER_HPP
