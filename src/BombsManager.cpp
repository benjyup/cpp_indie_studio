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
	_pm(pm)

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
//  for (auto &i : _bombs)
//    {
//      if (i->alreadyBlowUp() && i->getMesh() != NULL)
//	{
//	  for (auto &j : Char)
//	    {
////	      for (auto &k : j->getMesh()->getAnimators())
//		{
//		  std::cerr << k- << std::endl;
////		  j.get()->getMesh()->removeAnimator(k);
//		  std::cerr << "Deleting Animation" << std::endl;
//		}
	      //remove animator de la bombe;
//	    }
//	  std::cerr << "Deleting Animation2" << std::endl;
//	  _sceneManager.addToDeletionQueue(i->getMesh());
//	  i->setMesh(NULL);
//	}
//    }
  for (auto &i : _bombs)
    {
      if (!i->getCollision() && !i->alreadyBlowUp() && checkChar(Char, i->getPos()))
	{
	  std::cerr << "Creating Colision" << std::endl;
	  _col.push_back(_sceneManager.createOctreeTriangleSelector(_mesh, i->getMesh()));
	  i->getMesh()->setTriangleSelector(_col.back());
	  i->setCollision(true);
	}
    }
  return (ret);
}

bool is::BombsManager::checkChar(std::list<std::shared_ptr<Character>> const &Char, irr::core::vector3df const &v)
{
  int j = 1;
  for (auto const &i : Char)
    {
      irr::core::vector3df const &v_char  = i->getPos();
      std::cerr << "Character pos " << (int)(v_char.X / SCALE)<< " " << (int)(v_char.Y / SCALE) << std::endl;
      std::cerr << "Bomb pos " << (int)(v.X / SCALE) << " " << (int)(v.Y / SCALE) << std::endl;
      if ((int)(v_char.X / SCALE) == (int)(v.X / SCALE) && (int)(v_char.Y / SCALE) == (int)(v.Y / SCALE))
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
	  scene::ISceneNodeAnimator* anim = _sceneManager.createCollisionResponseAnimator(
		  i, c.get()->getMesh(), core::vector3df(6,10,6),
		  core::vector3df(0,0,0), core::vector3df(0,0,0));
	  c.get()->getMesh()->addAnimator(anim);
//	  anim->drop();
	}
      std::cerr << "Collision Added" << std::endl;
    }
  _col.clear();
}