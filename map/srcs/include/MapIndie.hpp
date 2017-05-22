//
// MapIndie.hpp for indie in /home/rodrigue.rene/TEST/DEPOT/cpp_indie_studio/map/srcs/MapIndie/include
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Sun May 21 00:05:16 2017 Rodrigue RENE
// Last update Sun May 21 09:50:06 2017 Rodrigue RENE
//

#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <irrlicht.h>
#include "ObjectMap.hpp"

namespace Indie
{
  class MapIndie
  {
    int							_length;
    int							_width;
    std::vector<Indie::IObject *>			_allObject;//A degager///////
    irr::scene::ISceneManager			       *_smgr;
    std::map<std::string , irr::scene::IAnimatedMesh *>	_theMeshs;
    std::map<std::string , irr::scene::ISceneNode*>	_theNodes;
    std::map<int, std::map<int, IObject *> >		_mapObjs;
    int							_X;
    int							_Y;
    int							_SCALE;
    irr::video::IVideoDriver				*_driver;
  public:
    MapIndie(std::string const &mapFile, irr::scene::ISceneManager *theSmgr,irr::video::IVideoDriver *driver);
    MapIndie(std::string const &file);
    ~MapIndie();
    
    void		setGround(std::string &);
    void		addObject(IObject *newObject);
    void		moveObject(Indie::IObject *newObject, Vector3d const &newPos);
    void		destroyObject(Indie::IObject *object);
    int			getWidth();
    int			getLength();
    int		        fillMap(std::string const &);
    int			fillMap2(int numLine, std::string const &line);
    TYPEOBJECT		whatsHere(Vector3d pos);
    void		addMesh(std::string);
    void		addTheGround(int x, int y);
    void		initMap();
  };
};
