//
// Created by kyxo on 5/30/17.
//

#include <map.hpp>

is::Character::Character(scene::IAnimatedMesh *node, video::ITexture *texture, scene::ISceneManager * smgr, core::vector3df const & pos)
		: _mesh(smgr->addAnimatedMeshSceneNode(node)), _text(texture), _smgr(smgr), _pos(pos), _speed(DEFAULT_SPEED), _bomb(DEFAULT_BOMB), _power(DEFAULT_POWER)
{
  if (_mesh)
    {
      _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
      _mesh->setMD2Animation(scene::EMAT_RUN);
      _mesh->setMaterialTexture( 0, _text);
      _mesh->setPosition(pos);
    }
}

void		is::Character::moove(is::Options::MOVES const &moove)
{
  irr::core::vector3df		v;

  v = _mesh->getPosition();
  if (moove == Options::MOVES::MOVE_UP)
    _mesh->setPosition(irr::core::vector3df(v.X, v.Y, v.Z + DEFAULT_SPEED));
}