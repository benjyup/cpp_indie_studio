//
// Created by kyxo on 5/22/17.
//

#include <iostream>
#include "map.hpp"

is::map::map(video::IVideoDriver *driver, scene::ISceneManager *smgr,
	std::vector<int> &map) : _driver(driver), _smgr(smgr), _map(map)
{
  _texture[0] = _driver->getTexture("./gfx/groundGrass.png");
  _texture[1] = _driver->getTexture("./gfx/wallBrick.png");
  _texture[2] = _driver->getTexture("./gfx/wallStone.png");
  _texture[3] = _driver->getTexture("./gfx/fire.png");
  scene::IAnimatedMesh *mesh = smgr->getMesh("./gfx/wallStone.obj");
  size = sqrt(map.size());
  for (int j = 0; j < map.size(); j++)
    {
      irr::scene::IAnimatedMeshSceneNode *node =
	      smgr->addAnimatedMeshSceneNode(mesh);
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      if (map[j] == 0)
	node->setPosition(irr::core::vector3df(j / size * SCALE, -SCALE,
					       (j % size) * SCALE));
      else
	node->setPosition(irr::core::vector3df((j / size) * SCALE, 0,
					       (j % size) * SCALE));
      node->setMaterialTexture(0, _texture[map[j]]);
      node->setScale(irr::core::vector3df(SCALE, SCALE, SCALE));
      node->setRotation(irr::core::vector3df(0, 0, 0));
      _mapi.push_back(node);
    }
  smgr->addCameraSceneNode(0, irr::core::vector3df(size / 2 * SCALE, 2000, size / 2 * 100),
			   irr::core::vector3df(size / 2 * SCALE, -SCALE, size / 2 * 160));
  moveObject(_mapi[10], Vector3d(10, 2, 10));
  delObject(_mapi[11]);
}

void is::map::moveObject(scene::IAnimatedMeshSceneNode *object, const Vector3d &v)
{
  int i = -1;
   while (++i < _mapi.size())
    if (_mapi[i] == object)
      {
	_mapi[i]->setPosition(irr::core::vector3df(v.getX() * SCALE, v.getY() * SCALE,
						   v.getZ() * SCALE));
	break ;
      }
}

void is::map::delObject(scene::IAnimatedMeshSceneNode *object)
{
  auto i = _mapi.begin();
  while (i != _mapi.end())
    {
      if (*i == object)
	{
	  _mapi.erase(i);
	  object->remove();
	  object->drop();
	  break ;
	}
      i++;
    }
}

//int	is::map::find(scene::IAnimatedMeshSceneNode *object)
//{
//  int i = -1;
//  while (++i < _mapi.size())
//    if (_mapi[i] == object)
//	return (i);
//  return (-1);
//}
//
//void	is::map::fire_up(Vector3d const &v, int level)
//{
//  int 	i = 0;
//
//  while (i < level || _mapi[v.Y * size + v.X] != 1)
//    {
//
//    }
//}
//void	is::map::burn(Vector3d const &v, int level)
//{
//	fire_up(v, level);
//}