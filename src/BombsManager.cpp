//
// Created by vincent on 12/06/17.
//

#include <iostream>
#include <thread>
#include "GameState.hpp"
#include "BombsManager.hpp"
#include "Fire.hpp"
#include <IndieStudioException.hpp>

is::BombsManager::BombsManager(is::map &map, irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager, is::PowerUpManager &pm) :
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager),
	_texture(NULL),
	_mesh(this->_sceneManager.getMesh("./gfx/bomb.obj")),
	_pm(pm),
	_mesh2(this->_sceneManager.getMesh("./gfx/wallBrick.obj"))
{
}

is::BombsManager::~BombsManager()
{

}

void is::BombsManager::putBomb(const irr::core::vector3df &pos, int power)
{
  this->_bombs.push_back(std::make_shared<Bomb>(this->_map, this->_texture, this->_mesh, pos, power, this->_videoDriver, this->_sceneManager, this->_pm));
}

bool is::BombsManager::checkBombsStatus(std::list<std::shared_ptr<is::Character>> const &Char)
{
  bool          ret = false;

  this->_bombs.remove_if([&](auto const &bomb) {
    ret = true;
    return bomb->blowUp(this->_bombs);
  });
  for (auto &i : _bombs)
    {
      if (!i->getCollision() && !i->alreadyBlowUp() && checkChar(Char, i->getPos2()))
	{
	  std::cerr << "Creating Colision" << std::endl;
	  irr::scene::IMeshSceneNode *node = _sceneManager.addOctreeSceneNode(_mesh2->getMesh(0), 0, 1);
	  node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	  _colNode[i->_id] = node;
	  _col[i->_id] = _sceneManager.createOctreeTriangleSelector(_mesh2, node);
	  node->setTriangleSelector(_col[i->_id]);
	  node->setScale(irr::core::vector3df(8, SCALE, 8));
	  node->setPosition({i->getPos().X + 8 / 2, 0, i->getPos().Z - 8 / 2});//{i->getPos2() * SCALE,  * SCALE, 2 * SCALE});
	  i->setCollision(true);
	}
  for (auto &i : _bombs)
    {
      if (i->getCollision() && i->alreadyBlowUp() && i->getMesh() != NULL)
	{
	  for (auto &j : Char)
	    {
	      if (j->getAnim(i->_id))
		j->getMesh()->removeAnimator(j->getAnim(i->_id));
		  std::cerr << "Deleting Animation" << std::endl;
	    }
	  _sceneManager.addToDeletionQueue(_colNode[i->_id]);
	  _sceneManager.addToDeletionQueue(i->getMesh());
	  i->setMesh(NULL);
	}
    }
    }
  return (ret);
}

bool is::BombsManager::checkChar(std::list<std::shared_ptr<Character>> const &Char, irr::core::vector3df const &v)
{
  int j = 1;
  for (auto const &i : Char)
    {
      irr::core::vector3df v_char  = {ceil(floor(i->getPos().Z) / (float) SCALE) - 1,
					     ceil(floor(i->getPos().X) / (float) SCALE), 0};

      std::cerr << "Character pos " << (int)(v_char.X) << " " << (int)(v_char.Y) << std::endl;
      std::cerr << "Bomb pos " << (int)(v.X)  << " " << (int)(v.Y) << std::endl;
      if (v_char.X == v.X && v_char.Y == v.Y)
	return false;
      std::cerr << j << std::endl;
      j++;
    }
  std::cerr << "I will Create the colision" << std::endl;
  return true;
}

void is::BombsManager::addCollision(std::list<std::shared_ptr<is::Character>> const &Char)
{
  for (auto const &i : _col)
    {
      std::cerr << "Adding collision" << std::endl;
      for (auto const &c : Char)
	{
	  c->pushAnim(_sceneManager.createCollisionResponseAnimator(
		  i.second, c->getMesh(), core::vector3df(4,6,4),
		  core::vector3df(0,0,0), core::vector3df(0,0,0)), i.first);
	  c.get()->getMesh()->addAnimator(c->getAnim(i.first));
	}
      std::cerr << "Collision Added" << std::endl;
    }
  _col.clear();
}