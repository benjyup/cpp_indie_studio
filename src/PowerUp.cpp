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
                    irr::core::vector3df const &pos,
                    is::map                     *map) : _mesh(smgr.addAnimatedMeshSceneNode(node)),
                                                       _text(texture),
                                                       _smgr(smgr),
                                                       _posMap(pos),
                                                       _posSpace(_posMap.Y * SCALE - SCALE / 2, 0.15 * SCALE, _posMap.X * SCALE + SCALE / 2),
                                                       _map(map)
{
    irr::video::SMaterial material;
    _node = node;
    _power = static_cast<is::poweris>(std::rand() % 3);
    if (!_mesh)
        throw is::IndieStudioException("Error while loading mesh");
    _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _mesh->setMD2Animation(irr::scene::EMAT_RUN);
    _mesh->setScale(irr::core::vector3df(1, 1, 1));
    _mesh->setMaterialTexture(0, _text);
    _mesh->setPosition(_posSpace);
    _mesh->setRotation(irr::core::vector3df(0, 270, 0));
    _mesh->getMaterial(0).Lighting = false;
    _mesh->getMaterial(0).NormalizeNormals = true;
    _map->addObject(Type::POWERUP, {(int)_posMap.X, (int)_posMap.Y, (int)_posMap.Z});
    std::cout << "MapPowerup : " << _posMap.X << ", " << _posMap.Y << ", " << _posMap.Y <<  std::endl;
    std::cerr << "New powerUp has been create !" << std::endl;
}

is::PowerUp::~PowerUp() {
    _mesh->remove();
    _map->delObject({(int)_posMap.X, (int)_posMap.Y, (int)_posMap.Z});
}

void is::PowerUp::getPower(is::Character *c) {
    switch (_power) {
        case is::poweris::POWERLIVE:
            c->incLive();
            break;
    };
}
