//
// Created by vincent on 17/06/17.
//

#include <iostream>
#include <IndieStudioException.hpp>
#include <MenuState.hpp>
#include "ChoosePlayerState.hpp"


std::vector<std::pair<std::string, std::string>>	is::ChoosePlayerState::GFX_PATH = {
	{"ButtonGFX/p1button.png", "ButtonGFX/p1buttonhovered.png"} ,
	{"ButtonGFX/p2button.png", "ButtonGFX/p2buttonhovered.png"},
	{"ButtonGFX/aionebutton.png", "ButtonGFX/aionebutton.png"},
	{"ButtonGFX/aitwobutton.png", "ButtonGFX/aitwobutton.png"},
	{"ButtonGFX/aithreebutton.png", "ButtonGFX/aithreebutton.png"},
	{"ButtonGFX/aifourbutton.png", "ButtonGFX/aifourbutton.png"}
};

is::ChoosePlayerState::ChoosePlayerState() :
	_buttons()
{

}

is::ChoosePlayerState::~ChoosePlayerState()
{

}

void is::ChoosePlayerState::Init(is::GameEngine *engine)
{
  //engine->getSceneManager()->createNewSceneManager();
  this->_options = &engine->getOptions();
  this->_gui = engine->getGuiEnv();
  this->_driver = engine->getDriver();
  this->_sceneManager = engine->getSceneManager();

  this->eventContext.engine  = engine;
  this->eventContext.buttons = &this->_buttons;
  this->eventContext.players = &this->_players;
  this->eventContext.nbrOfPlayers = 0;
  this->eventContext.nbrOfAI = 0;
  this->eventContext.gfxAI = &this->_gfxAI;
  this->eventContext.gfxPlayer = &this->_gfxPlayer;

  this->choosePlayerEventReceiver.init(&this->eventContext);
  engine->getDevice()->setEventReceiver(&this->choosePlayerEventReceiver);

  if (!(this->_voidButton = this->_driver->getTexture("ButtonGFX/voidbutton.png")) ||
      !(this->_voidButtonHovered = this->_driver->getTexture("ButtonGFX/voidbuttonhovered.png")))
    throw is::IndieStudioException("Error on loading playerChoose.");

  int 		i = 0;
  for (int y = 0 ; y < _gfxPlayer.size(); ++y)
    {
      if (!(_gfxPlayer[y].first = this->_driver->getTexture(GFX_PATH.at(i).first.c_str())) ||
	  !(_gfxPlayer[y].second = this->_driver->getTexture(GFX_PATH.at(i).second.c_str())))
	throw is::IndieStudioException("Error on loading playerChoose.");
      i += 1;
    }
  for (int y = 0 ; y < _gfxAI.size(); ++y)
    {
      if (!(_gfxAI[y].first = this->_driver->getTexture(GFX_PATH.at(i).first.c_str())) ||
	  !(_gfxAI[y].second = this->_driver->getTexture(GFX_PATH.at(i).second.c_str())))
	throw is::IndieStudioException("Error on loading playerChoose.");
      i += 1;
    }

  for (int y = 0 ; y < 4 ; ++y)
    this->_players.emplace_back(Player::PlayerType::VOID, "");

  MenuState::BUTTON_WIDTH;

  this->_buttons.emplace_back(10,
			      engine->getWindowSize().Y  / 4,
			      MenuState::BUTTON_WIDTH + 10,
			      engine->getWindowSize().Y / 4 + MenuState::BUTTON_HEIGHT,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS1,
			      L"",
			      L"");
  this->_buttons.emplace_back(10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 1,
			      MenuState::BUTTON_WIDTH + 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS2,
			      L"",
			      L"");
  this->_buttons.emplace_back(10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      MenuState::BUTTON_WIDTH + 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 3,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS3,
			      L"",
			      L"");
  this->_buttons.emplace_back(10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 3,
			      MenuState::BUTTON_WIDTH + 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 4,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_POS4,
			      L"",
			      L"");
  this->_buttons.emplace_back(engine->getWindowSize().X - MenuState::BUTTON_WIDTH - 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 1,
			      engine->getWindowSize().X - 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_PLAYER,
			      L"",
			      L"");
  this->_buttons.emplace_back(engine->getWindowSize().X - MenuState::BUTTON_WIDTH - 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      engine->getWindowSize().X - 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 3,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_AI,
			      L"",
			      L"");
  this->_drawButtons();
  this->_buttons[this->_buttons.size() - 2]->setImage(this->_voidButton);
  this->_buttons[this->_buttons.size() - 2]->setPressedImage(this->_voidButtonHovered);
  this->_buttons.back()->setImage(this->_voidButton);
  this->_buttons.back()->setPressedImage(this->_voidButtonHovered);
  std::cerr << "Buttons = " << _buttons.size() << std::endl;
}

void is::ChoosePlayerState::Cleanup(void)
{

}

void is::ChoosePlayerState::Pause(void)
{

}

void is::ChoosePlayerState::Resume(void)
{

}

void is::ChoosePlayerState::HandleEvents(void)
{

}

void is::ChoosePlayerState::Update(void)
{

}

void is::ChoosePlayerState::Draw(void)
{
  irr::u32 		nbrOfPlayers = 0;
  irr::u32 		nbrOfAI = 0;
  irr::u32 		i = 0;

  this->_driver->beginScene();
  this->_sceneManager->drawAll();
  for (auto b : this->_buttons)
    {
      if (i < 4)
	//b->setImage();
	{
	  if (this->_players[i].getType() == Player::PlayerType::PLAYER)
	    {
	      b->setImage(this->_gfxPlayer[nbrOfPlayers].first);
	      b->setPressedImage(this->_gfxPlayer[nbrOfPlayers].second);
	      nbrOfPlayers += 1;
	    } else
	    if (this->_players[i].getType() == Player::PlayerType::AI)
	      {
		b->setImage(this->_gfxAI[nbrOfAI].first);
		b->setPressedImage(this->_gfxAI[nbrOfAI].second);
		nbrOfAI += 1;
	      } else
	      {
		b->setImage(this->_voidButton);
		b->setPressedImage(this->_voidButtonHovered);
	      }
	}
      b->draw();
      i += 1;
    }
  this->_driver->endScene();
}

void is::ChoosePlayerState::ChangeState(is::GameEngine *engine, is::IGameState *state)
{

}

void is::ChoosePlayerState::_drawButtons()
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