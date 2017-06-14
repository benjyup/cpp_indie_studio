//
// Created by Jean-Adrien on 13/06/17.
//

#include <unistd.h>
#include <iostream>
#include "Character.hpp"
#include "PowerUp.hpp"

is::PowerUp::PowerUp(irr::scene::IAnimatedMesh *node,
                    irr::video::ITexture *texture,
                    irr::scene::ISceneManager &smgr,
                    irr::core::vector3df const &pos) : _mesh(smgr.addAnimatedMeshSceneNode(node)),
                                                       _text(texture),
                                                       _smgr(smgr),
                                                       _pos(pos)
{
    irr::scene::ITriangleSelector	*t;
    irr::video::SMaterial material;
    _node = node;
    if (_mesh)
    {
        _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _mesh->setMD2Animation(irr::scene::EMAT_RUN);
        _mesh->setScale(irr::core::vector3df(1, 1, 1));
        _mesh->setMaterialTexture(0, _text);
        _mesh->setPosition(pos);
        _mesh->setRotation(irr::core::vector3df(0, 270, 0));
        _mesh->getMaterial(0).Lighting = true;
        _mesh->getMaterial(0).NormalizeNormals = true;
        t = smgr.createTriangleSelector(_mesh);
        _mesh->setTriangleSelector(t);
        t->drop();
    }
}

void is::PowerUp::update(irr::core::vector3df &vec) {
    if ((vec.X > _pos.X - 10 && vec.X < _pos.X + 10) &&
            (vec.Y > _pos.Y - 10 && vec.Y < _pos.Y + 10))
        _mesh->remove();
}
