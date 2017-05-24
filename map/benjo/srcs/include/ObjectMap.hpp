//
// Objects.hpp for indie in /home/rodrigue.rene/TEST/DEPOT/cpp_indie_studio/map/srcs/MapIndie/include
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Sun May 21 00:25:08 2017 Rodrigue RENE
// Last update Sun May 21 15:06:34 2017 Rodrigue RENE
//

#pragma once
#include <irrlicht.h>
#include "IObject.hpp"

namespace Indie
{
  class ObjectMap :public Indie::IObject
  {
    std::string					_name;
    TYPEOBJECT					_type;
    Vector3d					_position;
    irr::scene::IAnimatedMeshSceneNode	       *_node;
    irr::scene::ISceneManager		       *_smgr;
    irr::video::IVideoDriver		       *_driver;
    int						_SCALE;
    // If a parameters is not used by the object (String for gameObject
    //  will do nothing

  public:
    ObjectMap();
    ObjectMap(int);
    ObjectMap(int,irr::scene::IAnimatedMesh *m, int scale,irr::scene::ISceneManager *theSmgr,irr::video::IVideoDriver* driver);
    // ObjectMap(int);
    ~ObjectMap();
    virtual void			setName(std::string const &);
    virtual void			setPosition(Vector3d const &);
    virtual void			setPosition(int,int,int);
    virtual std::string const    &getName() const;
    virtual Vector3d const       &getPosition() const;
    virtual void		setType(TYPEOBJECT const);
    TYPEOBJECT			getType() const;
   virtual  void			changeType(Indie::TYPEOBJECT newType);
    virtual void			burn();
  };
}
