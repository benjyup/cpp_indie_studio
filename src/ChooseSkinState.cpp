//
// Created by vincent on 18/06/17.
//

#include <IndieStudioException.hpp>
#include <iostream>
#include <map.hpp>
#include "ChooseSkinState.hpp"

const std::vector<std::pair<std::string, std::vector<std::string>>>		is::ChooseSkinState::MESH_PATH = {
	{"models/player/cartman/tris.md2",
		{
			"models/player/cartman/blue.pcx",
			"models/player/cartman/black.pcx",
			"models/player/cartman/eric.pcx",
			"models/player/cartman/green.pcx",
			"models/player/cartman/ghost.pcx"
		}
	},
	{"models/player/chef/tris.md2",
		{
			"models/player/chef/chef.pcx"
		}
	},
	{"models/player/kenny/tris.md2",
		{
			"models/player/kenny/kenny.pcx",
		}
	},
	{"models/player/kyle/tris.md2",
		{
			"models/player/kyle/kyle.pcx"
		}
	},
	{"models/player/marvin/tris.md2",
		{
			"models/player/marvin/marvin.pcx",
			"models/player/marvin/skin.pcx"
		}
	},
	{"models/player/stan/tris.md2",
		{
			"models/player/stan/stan.pcx"
		}
	}
};

is::ChooseSkinState::ChooseSkinState() : _current_index(1)
{

}

is::ChooseSkinState::~ChooseSkinState()
{

}

void is::ChooseSkinState::Init(is::GameEngine *engine)
{
  engine->getDevice()->setEventReceiver(NULL);
  //engine->getSceneManager()->createNewSceneManager();

  this->_gui = engine->getGuiEnv();
  this->_driver = engine->getDriver();
  this->_sceneManager = engine->getSceneManager();

  this->_sceneManager->addCameraSceneNode(0,
					  irr::core::vector3df(((0.5f + (BLOCK - 2))) * SCALE,
							       100,
							       ((0.5f + BLOCK * SCALE))),
					  irr::core::vector3df((((0.5f + (BLOCK - 2))) * SCALE / 2) - 2,
							       0,
							       (((0.5f + BLOCK * SCALE))) / 2) - 2);

  irr::scene::IAnimatedMesh 		*mesh;
  irr::video::ITexture			*texture;

  for (const auto &it : MESH_PATH)
    {
      irr::scene::ISceneNodeAnimator	*anim = this->_sceneManager->createRotationAnimator(irr::core::vector3df(0, 0.5f, 0));
      std::pair<irr::scene::IAnimatedMeshSceneNode *, std::vector<irr::video::ITexture*>> p;
      if (!(mesh = this->_sceneManager->getMesh(it.first.c_str())) ||
	  !(p.first = this->_sceneManager->addAnimatedMeshSceneNode(mesh)))
	throw is::IndieStudioException("error");
      for (const auto &it2 : it.second)
	{
	  if (!(texture = this->_driver->getTexture(it2.c_str())))
	    throw is::IndieStudioException("error");
	  p.second.push_back(texture);
	  std::cout << "FIN SECOND BOUCLE" << std::endl;
	}
      p.first->setVisible(false);
      p.first->setMaterialTexture(0, p.second.front());
      p.first->addAnimator(anim);
      p.first->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      p.first->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_STAND);
      this->_meshes.push_back(p);
      std::cout << "FIN FIRST BOUCLE" << std::endl;
      anim->drop();
    }
  std::cout << "FINI" << std::endl;
}

void is::ChooseSkinState::Cleanup(void)
{

}

void is::ChooseSkinState::Pause(void)
{

}

void is::ChooseSkinState::HandleEvents(void)
{

}

void is::ChooseSkinState::Resume(void)
{

}

void is::ChooseSkinState::Update(void)
{

}

void is::ChooseSkinState::Draw(void)
{
  this->_driver->beginScene();

  if (this->_current_index > 0)
    {
      this->_meshes[_current_index - 1].first->setVisible(true);
      this->_meshes[_current_index - 1].first->setPosition({((0.5f + (BLOCK - 2))) * SCALE - 180, 50, (((0.5f + (BLOCK - 2))) * SCALE - 20)});
    }

  this->_meshes[_current_index].first->setVisible(true);
  this->_meshes[_current_index].first->setPosition({((0.5f + (BLOCK - 2))) * SCALE - 70, 50, ((0.5f + (BLOCK - 2))) * SCALE - 50});

  if (this->_current_index < this->_meshes.size())
    {
      this->_meshes[_current_index + 1].first->setVisible(true);
      this->_meshes[_current_index + 1].first->setPosition({((0.5f + (BLOCK - 2))) * SCALE  + 0, 50, ((0.5f + (BLOCK - 2))) * SCALE - 150});
    }
  this->_sceneManager->drawAll();
  this->_driver->endScene();
}

void is::ChooseSkinState::ChangeState(is::GameEngine *engine, is::IGameState *state)
{

}
