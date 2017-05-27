//
// Created by peixot_b on 24/05/17.
//

#include "PlanetSystem.hpp"

PlanetSystem::PlanetSystem(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, const irr::io::path &filename,
			   irr::f32 radius, irr::f32 speed, irr::core::vector3df position)
{
  irr::scene::ISceneNode* node = 0;

  node = smgr->addLightSceneNode(0, irr::core::vector3df(50,50,50),
				 irr::video::SColorf(1.0f, 0.6f, 0.7f, 0.0f), 800.0f);
  irr::scene::ISceneNodeAnimator* anim = 0;
  anim = smgr->createFlyCircleAnimator(irr::core::vector3df(0,150,0), radius, speed);
  node->addAnimator(anim);
  anim->drop();
  node = smgr->addBillboardSceneNode(node, irr::core::dimension2d<irr::f32>(50, 50));
  node->setPosition(irr::core::vector3df(position));
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  node->setMaterialTexture(0, driver->getTexture(filename));
}

PlanetSystem::~PlanetSystem()
{

}

