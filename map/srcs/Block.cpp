//
// Created by kyxo on 5/23/17.
//

#include "Block.hpp"

namespace is
{
  Block::Block(Vector3d const &posi) : pos(posi)
  {
  }

  Block::~Block()
  {
  }

  Block &Block::operator=(Block const &other)
  {
    pos = other.pos;
    node = other.node;
    type = other.type;
  }

  void Block::init(Type t, video::ITexture *text, int size)
  {
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    printf("pos : %d\nvector : %d\n", pos % size, this->pos.getY());
    type = t;
    if (type == Type::GRASS) {
      node->remove();
      return;
    }
      else
      node->setPosition(irr::core::vector3df((this->pos.getX()) * SCALE, 0,
					       (this->pos.getY()) * SCALE));
    node->setMaterialTexture(0, text);
    node->setScale(irr::core::vector3df(SCALE, SCALE, SCALE));
    node->setRotation(irr::core::vector3df(0, 0, 0));
  }

  is::Type 	Block::getType() const
  {
	return (type);
  }

  void	Block::setType(is::Type &t)
  {
	type = t;
  }
}