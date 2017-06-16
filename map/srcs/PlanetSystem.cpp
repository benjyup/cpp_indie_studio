//
// Created by peixot_b on 24/05/17.
//

#include "PlanetSystem.hpp"

is::PlanetSystem::PlanetSystem(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, const irr::io::path &filename,
			   irr::f32 radius, irr::f32 speed, irr::core::vector3df position)
{
  _node = smgr->addLightSceneNode(0, irr::core::vector3df(50,50,50),
				 irr::video::SColorf(1.0f, 0.6f, 0.7f, 0.0f), 800.0f);
  irr::scene::ISceneNodeAnimator* anim = 0;
  anim = smgr->createFlyCircleAnimator(irr::core::vector3df(0,150,0), radius, speed);
  _node->addAnimator(anim);
  anim->drop();
  _node = smgr->addBillboardSceneNode(_node, irr::core::dimension2d<irr::f32>(50, 50));
  _node->setPosition(irr::core::vector3df(position));
  _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  _node->setMaterialTexture(0, driver->getTexture(filename));
}

is::PlanetSystem::~PlanetSystem()
{

}

void is::PlanetSystem::draw()
{
  _node->render();
}
