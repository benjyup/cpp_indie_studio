//
// Objects.cpp for indie in /home/rodrigue.rene/TEST/DEPOT/cpp_indie_studio/map/srcs
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Sun May 21 03:23:14 2017 Rodrigue RENE
// Last update Sun May 21 15:12:17 2017 Rodrigue RENE
//

#include <iostream>
#include "ObjectMap.hpp"

Indie::TYPEOBJECT   determineType(int type)
{
  if (type < 7 && type > -1)
    return (static_cast<Indie::TYPEOBJECT>(type));
  return (Indie::TYPEOBJECT::UNDEFINED);
}

std::string   const determineType_str(int type)
{
  if (type == 1)
    return ("./gfx/nothing.png");
  if (type == 0)
    return ("./gfx/groundGrass.png");
  return ("./gfx/groundGrass.png");
}

Indie::ObjectMap::ObjectMap() : _position(0,0,0), _type(Indie::TYPEOBJECT::UNDEFINED)
{

}

Indie::ObjectMap::ObjectMap(int type) : _position(0,0,0), _type(determineType(type))
{

}


Indie::ObjectMap::ObjectMap(int type, irr::scene::IAnimatedMesh *m, int scale,irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver) : _position(0,0,0)
{
  _smgr = smgr;
  _node = _smgr->addAnimatedMeshSceneNode(m);

  _type = determineType(type);
  _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _node->setMD2Animation(irr::scene::EMAT_STAND);
  _node->setMaterialTexture( 0, driver->getTexture(determineType_str(type).c_str()) );
  _node->setScale(irr::core::vector3df(scale, scale, scale));
  //_node->setMaterialType( irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  _driver = driver;
  _SCALE = scale;
}

Indie::ObjectMap::~ObjectMap()
{

}

void			Indie::ObjectMap::setName(std::string const &newName)
{
  _name = newName;
}

void			Indie::ObjectMap::setPosition(Vector3d const &newPos)
{
  _position = newPos;
  _node->setPosition(irr::core::vector3df(newPos.getX(),newPos.getY(),newPos.getZ()));
}

void			Indie::ObjectMap::setPosition(int x, int y, int z)
{
  _position.setAll(x, y, z);
  _node->setPosition(irr::core::vector3df(x, y,  z));
}

std::string const    &Indie::ObjectMap::getName() const
{
  return (_name);
}

Indie::Vector3d const       &Indie::ObjectMap::getPosition() const
{
  return (_position);
}

void			Indie::ObjectMap::setType(TYPEOBJECT const type)
{
  _type = type;
}

Indie::TYPEOBJECT			Indie::ObjectMap::getType() const
{
  return (_type);
}

void			Indie::ObjectMap::changeType(Indie::TYPEOBJECT newType)
{
  _type = newType;
  _node->setMaterialTexture( 0, _driver->getTexture(determineType_str(_type).c_str()));
}

void			Indie::ObjectMap::burn()
{
  _type = Indie::TYPEOBJECT::FIRE;
  _node->setMaterialTexture( 0, _driver->getTexture(determineType_str(_type).c_str()));
}
