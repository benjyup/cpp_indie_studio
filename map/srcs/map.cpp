//
// Created by kyxo on 5/22/17.
//

#include <iostream>
#include "map.hpp"
#include "Fire.hpp"
#include "PlanetSystem.hpp"
#include "Camera.hpp"

is::map::map(video::IVideoDriver *driver, scene::ISceneManager *smgr,
	     std::vector<int> &map) : _driver(driver), _smgr(smgr), _map(map)
{
  irr::scene::ITriangleSelector *t;

  _texture[0] = _driver->getTexture("./gfx/groundGrass.png");
  _texture[1] = _driver->getTexture("./gfx/wallBrick.png");
  _texture[2] = _driver->getTexture("./gfx/wallStone.png");
  _texture[3] = _driver->getTexture("./gfx/fire.png");
  scene::IAnimatedMesh *mesh = smgr->getMesh("./gfx/wallStone.obj");
  size = sqrt(map.size());
  //camera->setTarget(core::vector3df(-70,30,-60));
  irr::scene::ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS();
  for (int j = 0; j < map.size(); j++)
    {
      Block b = is::Block(Vector3d(j / size, j % size, 0));
      b.node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, 1);
      t = smgr->createOctreeTriangleSelector(b.node->getMesh(), b.node);
      b.node->setTriangleSelector(t);
      b.init((Type) map[j], _texture[map[j]], size);
      _mapi.push_back(b);
    }
  initEffects();

  //Camera	cam(smgr, MENU, );
  //cam.setMenuMode();
  //cam.setMenuMode();

//  moveObject(_mapi[10], Vector3d(10, 2, 10));
//  delObject(_mapi[0]);
//if (canIMoove(Vector3d(0, 0, 0)))
//  printf("yes\n");
//  addObject(BREAK, Vector3d(0, 0, 0));
//  if (canIMoove(Vector3d(0, 0, 0)))
//    printf("yes\n");
}

void is::map::initEffects()
{
  Fire		fire(_smgr, _driver, irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, 0.5 * SCALE), TOP, 3);
  Fire		fire2(_smgr, _driver, irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, (0.5 + (BLOCK - 1)) * SCALE), TOP, 3);
  Fire 		fire3(_smgr, _driver, irr::core::vector3df((0.5 + (BLOCK - 2)) * SCALE, 0.5 * SCALE, 0.5 * SCALE), TOP, 3);
  Fire 		fire4(_smgr, _driver, irr::core::vector3df((0.5 + (BLOCK - 2)) * SCALE, 0.5 * SCALE, (0.5 + (BLOCK - 1)) * SCALE), TOP, 3);
  PlanetSystem 	PlanetR(_smgr, _driver, "./gfx/particlered.bmp", 800.0f, 0.001f,
			      irr::core::vector3df(6.0 * SCALE, 0.5 * SCALE, 7 * SCALE));
  PlanetSystem 	PlanetW(_smgr, _driver, "./gfx/particlewhite.bmp", 600.0f, 0.0009f,
			      irr::core::vector3df(6.0 * SCALE, 0.5 * SCALE, 7 * SCALE));
  PlanetSystem 	PlanetG(_smgr, _driver, "./gfx/particlegreen.jpg", 400.0f, 0.0008f,
			      irr::core::vector3df(6.0 * SCALE, 0.5 * SCALE, 7 * SCALE));
  _smgr->addSkyDomeSceneNode(_driver->getTexture("./gfx/space3.jpg"), 16, 16, 1.0f, 1.0f)->setRotation(
	  irr::core::vector3df(0, 0, -180));
  _smgr->addSkyDomeSceneNode(_driver->getTexture("./gfx/space3.jpg"), 16, 16, 1.0f, 1.0f);
}

void 	is::map::moveObject(Block &object, const Vector3d &v)
{
  int i = -1;
  while (++i < _mapi.size())
    if (_mapi[i].node == object.node)
      {
	_mapi[i].node->setPosition(irr::core::vector3df(v.getX() * SCALE, v.getY() * SCALE,
							v.getZ() * SCALE));
	_mapi[i].pos.setX(v.getX());
	_mapi[i].pos.setY(v.getY());
	_mapi[i].pos.setZ(v.getZ());
	break ;
      }
}

void 	is::map::delObject(Block &object)
{
  int i = 0;
  irr::core::vector3df v;
  if ((i = find(object)) == -1)
    return;
  object.node->setMaterialTexture(0, _texture[GRASS]);
  v = object.node->getPosition();
  v.Y = -SCALE;
  object.type = GRASS;
  object.node->setPosition(v);
}

bool 	is::map::canIMoove2(Vector3d const &pos) const
{
  int 		posi = 0;

  if ((posi = find(pos)) == -1)
    {
      std::cout << "return false" << std::endl;
      return (false);
    }
  printf("posi : %d\n",posi);
  if (_mapi[posi].type == Type::GRASS)
    {
      std::cout << "Return true" << std::endl;
      return (true);
    }
  else
    {
      std::cout << pos << " pos.z = " << pos.getZ() << std::endl;
      if (_mapi[posi].type == Type::BREAK)
	std::cout << "type = BREAK" << std::endl;
      if (_mapi[posi].type == Type::FIRE)
	std::cout << "type = FIRE" << std::endl;
      if (_mapi[posi].type == Type::WALL)
	std::cout << "type = WALL" << std::endl;
    }
  return (false);
}

bool 	is::map::canIMoove(Vector3d const &pos) const
{
  int 		posi = 0;

  if ((posi = find(pos)) == -1)
    return (false);
  printf("posi : %d\n",posi);
  if (_mapi[posi].type == Type::GRASS)
    return (true);
  return (false);
}


int	is::map::find(Block const &b) const
{
  int i = -1;
  while (++i < _mapi.size())
    if (_mapi[i].node == b.node)
      return (i);
  return (-1);
}

int 	is::map::find(Vector3d const &v) const
{
  int 	posi = 0;

  if ((posi = v.getY() * size + v.getX()) < 0 || posi > size * size)
    return (-1);
  return (posi);
}

void 	is::map::addObject(int t, Vector3d const &pos)
{
  int i = 0;
  irr::core::vector3df v;

  if ((i = find(pos)) == -1 || _mapi[i].type != Type::GRASS)
    {
      std::cout << "Can't add Block, Already something there" << std::endl;
      return ;
    }
  _mapi[i].node->setMaterialTexture(0, _texture[t]);
  v = _mapi[i].node->getPosition();
  v.Y = 0;
  _mapi[i].node->setPosition(v);
  _mapi[i].type = (Type)t;
  return;
}
