//
// Created by vincent on 18/06/17.
//

#include <IndieStudioException.hpp>
#include <iostream>
#include <map.hpp>
#include <MenuState.hpp>
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

const std::vector<std::pair<std::string, std::string>>		is::ChooseSkinState::BUTTON_GFX_PATH = {
	{"ButtonGFX/arrowupbutton.png", "ButtonGFX/arrowupbuttonhovered.png"},
	{"ButtonGFX/arrowdownbutton.png", "ButtonGFX/arrowdownbuttonhovered.png"},
	{"ButtonGFX/arrowrightbutton.png", "ButtonGFX/arrowrightbuttonhovered.png"},
	{"ButtonGFX/arrowleftbutton.png", "ButtonGFX/arrowleftbuttonhovered.png"},
	{"ButtonGFX/applybutton.png", "ButtonGFX/applybuttonhovered.png"}
};

is::ChooseSkinState::ChooseSkinState(irr::u32 player) : _player(player)
{

}

is::ChooseSkinState::~ChooseSkinState()
{

}

void is::ChooseSkinState::Init(is::GameEngine *engine)
{
  engine->getDevice()->setEventReceiver(NULL);
  
  this->_options = &engine->getOptions();
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

  this->_buttons.emplace_back(engine->getWindowSize().X /2 - MenuState::BUTTON_WIDTH / 2,
			      10,
			      engine->getWindowSize().X /2 + MenuState::BUTTON_WIDTH / 2,
			      10 + MenuState::BUTTON_HEIGHT,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_UP_ARROW);

  this->_buttons.emplace_back(engine->getWindowSize().X / 2 - MenuState::BUTTON_WIDTH / 2,
			      engine->getWindowSize().Y - MenuState::BUTTON_HEIGHT - 10,
			      engine->getWindowSize().X / 2 + MenuState::BUTTON_WIDTH / 2,
			      engine->getWindowSize().Y - 10,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_DOWN_ARROW);

  this->_buttons.emplace_back(engine->getWindowSize().X  - MenuState::BUTTON_WIDTH - 10,
			      engine->getWindowSize().Y / 2 - MenuState::BUTTON_HEIGHT / 2 - 10,
			      engine->getWindowSize().X - 10,
			      engine->getWindowSize().Y / 2 + MenuState::BUTTON_HEIGHT / 2 - 10,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_RIGHT_ARROW);

  this->_buttons.emplace_back(10,
			      engine->getWindowSize().Y / 2 - MenuState::BUTTON_HEIGHT / 2 - 10,
			      10 + MenuState::BUTTON_WIDTH,
			      engine->getWindowSize().Y / 2 + MenuState::BUTTON_HEIGHT / 2 - 10,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_LEFT_ARROW);

  this->_buttons.emplace_back(engine->getWindowSize().X  - MenuState::BUTTON_WIDTH - 10,
			      engine->getWindowSize().Y - MenuState::BUTTON_HEIGHT - 10,
			      engine->getWindowSize().X - 10,
			      engine->getWindowSize().Y - 10,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_SKIN_APPLY);

  this->_drawButtons();

  irr::u32 i = 0;
  irr::video::ITexture		*default_texture = NULL;
  irr::video::ITexture		*hovered_texture = NULL;
  for (auto &b : this->_buttons)
    {
      if (!(default_texture = this->_driver->getTexture(BUTTON_GFX_PATH.at(i).first.c_str())) ||
	  !(hovered_texture = this->_driver->getTexture(BUTTON_GFX_PATH.at(i).second.c_str())))
	throw is::IndieStudioException("Error.");
      b->setImage(default_texture);
      b->setPressedImage(hovered_texture);
      i += 1;
    }

  this->_context.engine = engine;
  this->_context.current_index = 0;
  this->_context.meshes = &this->_meshes;
  this->_context.apply = false;

  this->_receiver.init(&this->_context);

  engine->getDevice()->setEventReceiver(&this->_receiver);
}

void is::ChooseSkinState::Cleanup(void)
{
  Camera c(this->_sceneManager, this->_driver, CamMode::MENU, this->_context.engine);
  c.setMenuMode();
  this->_context.engine->getDevice()->setEventReceiver(NULL);
}

void is::ChooseSkinState::Pause(void)
{

}

void is::ChooseSkinState::HandleEvents(void)
{

}

void is::ChooseSkinState::Resume(void)
{
  this->_drawButtons();
}

void is::ChooseSkinState::Update(void)
{

}

void is::ChooseSkinState::Draw(void)
{
  if (this->_context.apply)
    {
      this->_options->getPlayers()[_player]
	      .setMeshPath(this->MESH_PATH.at(this->_context.current_index).first);
      this->_options->getPlayers()[_player]
	      .setTexturePath(this->MESH_PATH.at(this->_context.current_index).second[0]);
      for (auto &it : this->_meshes)
	it.first->remove();
      this->_context.engine->getDevice()->setEventReceiver(NULL);
      this->_context.engine->PopState();
      return ;
    }

  this->_driver->beginScene();

  this->_drawMeshes();

  this->_sceneManager->drawAll();
  for (const auto &b : this->_buttons)
    b->draw();
  this->_driver->endScene();
}

void is::ChooseSkinState::_drawMeshes()
{
  for (auto &m : this->_meshes)
    m.first->setVisible(false);

  std::cout << "current_index = " << _context.current_index << std::endl;
  if (this->_context.current_index > 0)
    {
      this->_meshes[this->_context.current_index - 1].first->setPosition({((0.5f + (BLOCK - 2))) * SCALE  + 0, 50, ((0.5f + (BLOCK - 2))) * SCALE - 150});
      this->_meshes[this->_context.current_index - 1].first->setVisible(true);
    }
  else
    {
      this->_meshes.back().first->setPosition({((0.5f + (BLOCK - 2))) * SCALE  + 0, 50, ((0.5f + (BLOCK - 2))) * SCALE - 150});
      this->_meshes.back().first->setVisible(true);
    }

  this->_meshes[this->_context.current_index].first->setPosition({((0.5f + (BLOCK - 2))) * SCALE - 70, 50, ((0.5f + (BLOCK - 2))) * SCALE - 50});
  this->_meshes[this->_context.current_index].first->setVisible(true);

  if (this->_context.current_index < this->_meshes.size() - 1)
    {
      this->_meshes[this->_context.current_index + 1].first->setPosition({((0.5f + (BLOCK - 2))) * SCALE - 180, 50, (((0.5f + (BLOCK - 2))) * SCALE - 20)});;
      this->_meshes[this->_context.current_index + 1].first->setVisible(true);
    }
  else
    {
      this->_meshes.front().first->setPosition({((0.5f + (BLOCK - 2))) * SCALE - 180, 50, (((0.5f + (BLOCK - 2))) * SCALE - 20)});;
      this->_meshes.front().first->setVisible(true);
    }
}

void is::ChooseSkinState::ChangeState(is::GameEngine *engine, is::IGameState *state)
{

}

void is::ChooseSkinState::_drawButtons()
{
  for (auto &it : this->_buttons)
    {
      it.set(this->_gui->addButton({it.getX(), it.getY(), it.getX2(), it.getY2()},
				   0,
				   it.getId(),
				   it.getText().c_str(),
				   it.getHint().c_str()));
      it->setUseAlphaChannel(true);
      it->setScaleImage(true);
    }
  for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT; ++i)
    {
      if (i != irr::gui::EGDC_BUTTON_TEXT)
	{
	  irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR) i);
	  col.set(0, 43, 50, 251);
	  _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, col);
	} else
	{
	  irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR) i);
	  col.set(255, 255, 255, 255);
	  _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, col);
	}
    }
}
