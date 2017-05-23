//
// MapIndie.cpp for indie in /home/rodrigue.rene/TEST/DEPOT/cpp_indie_studio/map/srcs
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Sun May 21 00:51:11 2017 Rodrigue RENE
// Last update Sun May 21 14:01:23 2017 Rodrigue RENE
//

#include <iostream>
#include <fstream>
#include "MapIndie.hpp"

Indie::MapIndie::MapIndie(std::string const &mapFile)
{
  fillMap(mapFile);
  _theMeshs.emplace("Cube", _smgr->getMesh("cube.obj"));
  addTheGround(0,0);
  initMap();
  //faire le setter de smgr
}

Indie::MapIndie::MapIndie(std::string const &mapFile, irr::scene::ISceneManager *theSmgr, irr::video::IVideoDriver *driver) : _SCALE(10)
{
  int i=0;
  _smgr = theSmgr;
  fillMap(mapFile);
  _driver = driver;
  _theMeshs.emplace("Cube", _smgr->getMesh("cube.obj"));
  addTheGround(0,0);
  initMap();
}

Indie::MapIndie::~MapIndie()
{

}

void	Indie::MapIndie::setGround(std::string &GroundFile)
{

}

void	Indie::MapIndie::addObject(IObject *newObject)
{
  _allObject.push_back(newObject); 
}

void	Indie::MapIndie::moveObject(Indie::IObject *newObject, Vector3d const &position)
{
  auto it = std::find(_allObject.begin(), _allObject.end(), newObject);

  if (it != _allObject.end())
    newObject->setPosition(position);  
}

void	Indie::MapIndie::destroyObject(Indie::IObject *object)
{
  auto it = std::find(_allObject.begin(), _allObject.end(), object);
  if (it != _allObject.end())
    _allObject.erase(it);  
}

int		Indie::MapIndie::getWidth()//Largeur
{
  return (_width);
}

int		Indie::MapIndie::getLength() //Longueur
{
  return (_length);
}

int  Indie::MapIndie::fillMap(std::string const &mapFile)
{
  std::ifstream file;
  std::string	buff;
  int		i = 0;
  file.open(mapFile);
  if (!file.good())
    return 4;
  int x = 0;
  while (!file.eof())
    {
      getline(file, buff, '\n');
      int max = fillMap2(i, buff);
      if (i == 0)
	  _X = max;
      i++;
    }
  _Y = i;
}

int  Indie::MapIndie::fillMap2(int numLine, std::string const &line)
{
  std::map<int, IObject *> tempo;
  int i, r = 0;
  std::cout<<"line ="<<line<<std::endl;
  for (i = 0;line[i] != 0;i++)
    {
      IObject *caseMap = new ObjectMap((int)line[i] - '0');
      std::cout<<"line ="<<line[i] - '0'<<std::endl;
      tempo.emplace(std::make_pair(i, caseMap));
    }
  _mapObjs.emplace(std::make_pair(numLine, tempo));
  return (i);
}

void	Indie::MapIndie::addTheGround(int x, int y)
{
  irr::scene::IAnimatedMesh *meshGround = _smgr->getMesh(0);
  meshGround =  _smgr->addHillPlaneMesh( "myHill",
					 irr::core::dimension2d<irr::f32>(_SCALE, _SCALE),//scale X Y
					 irr::core::dimension2d<irr::u32> (2 ,2), 0, 10,//X * scale Y * scale
					 irr::core::dimension2d<irr::f32>(0,0),//??????
					 irr::core::dimension2d<irr::f32>(0,0));//????
  _theNodes.emplace("Ground", _smgr->addAnimatedMeshSceneNode( meshGround ));
  _theMeshs.emplace("Ground", meshGround);
}

void	Indie::MapIndie::initMap()
{
  int y = 0;
  for ( auto it = _mapObjs.find(y); it!= _mapObjs.end(); y++)
    {
      int x = 0;
      for (auto it2 = it->second.find(x);it2 != it->second.end(); x++)
	{
	  Indie::TYPEOBJECT typeTempo = it2->second->getType();

	  irr::scene::IAnimatedMesh *m = _theMeshs.find("Cube")->second;
	  IObject *caseMapSol = new ObjectMap((int) Indie::TYPEOBJECT::UNDEFINED, m, _SCALE, _smgr,_driver);

	  caseMapSol->setPosition(x * _SCALE, -_SCALE, y * _SCALE);

	  if (typeTempo != Indie::TYPEOBJECT::UNDEFINED)
	    {
	      delete it2->second;
	      IObject *caseMap = new ObjectMap((int) typeTempo, m, _SCALE, _smgr,_driver);

	      it2->second = caseMap;
	      it2->second->setPosition(x * _SCALE, 0, y * _SCALE);
	    }
	  it2++;
	}
      it++;
    }
}
