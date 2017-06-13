//
// Created by kyxo on 5/30/17.
//

#include <map.hpp>
#include <iostream>

is::Character::Character(scene::IAnimatedMesh *node, video::ITexture *texture, scene::ISceneManager * smgr, core::vector3df const & pos)
		: _mesh(smgr->addAnimatedMeshSceneNode(node)), _text(texture), _smgr(smgr), _pos(pos), _speed(DEFAULT_SPEED), _bomb(DEFAULT_BOMB), _power(DEFAULT_POWER)
{
  irr::scene::ITriangleSelector	*t;
  video::SMaterial material;

  if (_mesh)
    {
      _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
     _mesh->setMD2Animation(scene::EMAT_RUN);
      _mesh->setScale(irr::core::vector3df(1, 1, 1));
      _mesh->setMaterialTexture(0, _text);
      _mesh->setPosition(pos);
      _dir = Character::DIR::TOP;
      _mesh->setRotation(irr::core::vector3df(0, 270, 0));
      _mesh->getMaterial(0).Lighting = true;
      _mesh->setScale({0.3f, 0.3f, 0.3f});
      _mesh->getMaterial(0).NormalizeNormals = true;
      t = smgr->createTriangleSelector(_mesh);
      _mesh->setTriangleSelector(t);
      t->drop();
    }

}

void		is::Character::moove(is::Options::MOVES const &moove)
{
  irr::core::vector3df v;

  v = _mesh->getPosition();
  switch (moove)
    {
      case (Options::MOVES::MOVE_UP) :
	{
	  if (_dir != is::Character::DIR::TOP)
	    {
	      _mesh->setRotation(irr::core::vector3df(0, 270, 0));
	      _dir = is::Character::DIR::TOP;
	    }
	  _mesh->setPosition(irr::core::vector3df(v.X, v.Y, v.Z + DEFAULT_SPEED));
	}
      break;
      case (Options::MOVES::MOVE_DOWN) :
	{
	  if (_dir != is::Character::DIR::DOWN)
	    {
	      _mesh->setRotation(irr::core::vector3df(0, 90, 0));
	      _dir = is::Character::DIR::DOWN;
	    }
	  _mesh->setPosition(irr::core::vector3df(v.X, v.Y, v.Z - DEFAULT_SPEED));
	}
      break;
      case (Options::MOVES::MOVE_RIGHT) :
	{
	  if (_dir != is::Character::DIR::RIGHT)
	    {
	      _mesh->setRotation(irr::core::vector3df(0, 0, 0));
	      _dir = is::Character::DIR::RIGHT;
	    }
	  _mesh->setPosition(irr::core::vector3df(v.X + DEFAULT_SPEED, v.Y, v.Z));
	}
      break;
      case (Options::MOVES::MOVE_LEFT):
	{
	  if (_dir != is::Character::DIR::LEFT)
	    {
	      _mesh->setRotation(irr::core::vector3df(0, 180, 0));
	      _dir = is::Character::DIR::LEFT;
	    }
	  _mesh->setPosition(irr::core::vector3df(v.X - DEFAULT_SPEED, v.Y, v.Z));
	}
      break;
      default:
	std::cout << "AUCUN" << std::endl;
    }
}