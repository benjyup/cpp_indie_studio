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
  _texture[Type::GRASS] = _driver->getTexture("./gfx/tile_aqua.png");
  _texture[Type::WALL] = _driver->getTexture("./gfx/wallStone.png");
  _texture[Type::BREAK] = _driver->getTexture("./gfx/wallBrick.png");
  _texture[Type::FIRE] = _texture[Type::GRASS];
  _texture[Type::BOMB] = _texture[Type::GRASS];
  _texture[Type::POWERUP] = _texture[Type::GRASS];
  scene::IAnimatedMesh *mesh = smgr->getMesh("./gfx/wallStone.obj");
  size = sqrt(map.size());
  irr::scene::ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS();
  int i  = 0;
  for (int j = 0; j < map.size(); j++)
    {
      Block b = is::Block(Vector3d(j / size, j % size, 0));
      b.node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, 1);
      _t.push_back(smgr->createOctreeTriangleSelector(mesh->getMesh(0), b.node));
      b.node->setTriangleSelector(_t.back());
      b.init((Type) map[j], _texture[map[j]], size);
      _mapi.push_back(b);
      std::cout << "map[" << i << "] = " << map[j] << std::endl;
      i++;
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

is::map::~map()
{
  _skyDown->remove();
  _skyUp->remove();
}

void is::map::initEffects()
{
  _fire1 = std::make_shared<Fire>(*this,
				  _smgr,
				  _driver,
				  irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, 0.5 * SCALE),
				  irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, 0.5 * SCALE),
				  TOP,
				  3);
  _fire2 = std::make_shared<Fire>(*this,
				  _smgr,
				  _driver,
				  irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, (0.5 + (BLOCK - 1)) * SCALE),
				  irr::core::vector3df(-0.5 * SCALE, 0.5 * SCALE, (0.5 + (BLOCK - 1)) * SCALE),
				  TOP,
				  3);
  _fire3 = std::make_shared<Fire>(*this,
				  _smgr,
				  _driver,
				  irr::core::vector3df((0.5 + (BLOCK - 2)) * SCALE, 0.5 * SCALE, 0.5 * SCALE),
				  irr::core::vector3df((0.5 + (BLOCK - 2)) * SCALE, 0.5 * SCALE, 0.5 * SCALE),
				  TOP,
				  3);
  _fire4 = std::make_shared<Fire>(*this,
				  _smgr,
				  _driver,
				  irr::core::vector3df((0.5 + (BLOCK - 2)) * SCALE,0.5 * SCALE, (0.5 + (BLOCK - 1)) * SCALE),
				  irr::core::vector3df((0.5 + (BLOCK - 2)) * SCALE,0.5 * SCALE, (0.5 + (BLOCK - 1)) * SCALE),
				  TOP,
				  3);
  _planetR = std::make_shared<PlanetSystem>(_smgr, _driver, "./gfx/particlered.bmp", 800.0f, 0.001f,
					    irr::core::vector3df(6.0 * SCALE, 0.5 * SCALE, 7 * SCALE));
  _planetW = std::make_shared<PlanetSystem>(_smgr, _driver, "./gfx/particlewhite.bmp", 600.0f, 0.0009f,
					    irr::core::vector3df(6.0 * SCALE, 0.5 * SCALE, 7 * SCALE));
  _planetG = std::make_shared<PlanetSystem>(_smgr, _driver, "./gfx/particlegreen.jpg", 400.0f, 0.0008f,
					    irr::core::vector3df(6.0 * SCALE, 0.5 * SCALE, 7 * SCALE));

  _skyDown = _smgr->addSkyDomeSceneNode(_driver->getTexture("./gfx/space3.jpg"), 16, 16, 1.0f, 1.0f);
  _skyDown->setRotation(irr::core::vector3df(0, 0, -180));
  _skyUp = _smgr->addSkyDomeSceneNode(_driver->getTexture("./gfx/space3.jpg"), 16, 16, 1.0f, 1.0f);
}

is::Block const	*is::map::findBlock(Vector3d const &v) const
{
  int 		i = 0;

  if ((i = find(v)) != -1)
    return (&_mapi[i]);
  return (NULL);
}

void	is::map::addCollision(irr::scene::ISceneNode *node)
{
  for (auto const & i : _t)
    {
      scene::ISceneNodeAnimator* anim = _smgr->createCollisionResponseAnimator(
	      i, node, core::vector3df(3,5,3),
	      core::vector3df(0,0,0), core::vector3df(1,3,1));
      node->addAnimator(anim);
      anim->drop();
    }
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

void 	is::map::delObject(Vector3d const &pos)
{
  int i = 0;
  irr::core::vector3df v;
  if ((i = find(pos)) == -1)
    return ;
  _mapi[i].node->setMaterialTexture(0, _texture[GRASS]);
  v = _mapi[i].node->getPosition();
  v.Y = -SCALE;
  _mapi[i].type = GRASS;
  _mapi[i].node->setPosition(v);
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
  return (_mapi[posi].type == Type::GRASS);
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

void 	is::map::addObject(Type t, Vector3d const &pos)
{
  int i = 0;
  irr::core::vector3df v;

  if ((i = find(pos)) == -1)
    {
      std::cout << "Can't add Block, Already something there" << std::endl;
      return ;
    }
  _mapi[i].node->setMaterialTexture(0, _texture[t]);
  v = _mapi[i].node->getPosition();
  _mapi[i].type = t;
  v.Y = _mapi[i].setY();
  _mapi[i].node->setPosition(v);
  return;
}

void	is::map::draw()
{
  _skyUp->render();
  _skyDown->render();
  _fire1->draw();
  _fire2->draw();
  _fire3->draw();
  _fire4->draw();
  _planetG->draw();
  _planetR->draw();
  _planetW->draw();
  for (auto it = _mapi.begin(); it != _mapi.end(); it++){
      it->draw();
    }
}