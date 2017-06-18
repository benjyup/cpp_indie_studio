//
// Created by vincent on 17/06/17.
//

#include <iostream>
#include <IndieStudioException.hpp>
#include <MenuState.hpp>
#include "ChoosePlayerState.hpp"
#include "ChooseSkinState.hpp"


std::vector<std::pair<std::string, std::string>>	is::ChoosePlayerState::GFX_PATH = {
	{"ButtonGFX/p1button.png", "ButtonGFX/p1buttonhovered.png"} ,
	{"ButtonGFX/p2button.png", "ButtonGFX/p2buttonhovered.png"},
	{"ButtonGFX/aionebutton.png", "ButtonGFX/aionebuttonhovered.png"},
	{"ButtonGFX/aitwobutton.png", "ButtonGFX/aitwobuttonhovered.png"},
	{"ButtonGFX/aithreebutton.png", "ButtonGFX/aithreebuttonhovered.png"},
	{"ButtonGFX/aifourbutton.png", "ButtonGFX/aifourbuttonhovered.png"}
};

const irr::u32 								is::ChoosePlayerState::VOID_BUTTON_INDEX = 0;
const irr::u32 								is::ChoosePlayerState::PLAY_BUTTON_INDEX = 1;
const irr::u32 								is::ChoosePlayerState::ADD_BOT_BUTTON_INDEX = 2;
const irr::u32 								is::ChoosePlayerState::ADD_PLAYER_BUTTON_INDEX = 3;
const irr::u32 								is::ChoosePlayerState::DELETE_BOT_BUTTON_INDEX = 4;
const irr::u32 								is::ChoosePlayerState::DELETE_PLAYER_BUTTON_INDEX = 5;

is::ChoosePlayerState::ChoosePlayerState() :
	_buttons()
{

}

is::ChoosePlayerState::~ChoosePlayerState()
{

}

void is::ChoosePlayerState::Init(is::GameEngine *engine)
{
  engine->getDevice()->setEventReceiver(NULL);
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
  this->eventContext.stop = false;
  this->eventContext.chooseSkin = false;

  this->choosePlayerEventReceiver.init(&this->eventContext);

  if (!(this->_buttonsTextures[VOID_BUTTON_INDEX].first = this->_driver->getTexture("ButtonGFX/voidbutton.png")) ||
      !(this->_buttonsTextures[VOID_BUTTON_INDEX].second = this->_driver->getTexture("ButtonGFX/voidbuttonhovered.png")) ||
      !(this->_buttonsTextures[PLAY_BUTTON_INDEX].first = this->_driver->getTexture("ButtonGFX/playbutton.png")) ||
      !(this->_buttonsTextures[PLAY_BUTTON_INDEX].second = this->_driver->getTexture("ButtonGFX/playbuttonhovered.png")) ||
      !(this->_buttonsTextures[ADD_BOT_BUTTON_INDEX].first = this->_driver->getTexture("ButtonGFX/addbotbutton.png")) ||
      !(this->_buttonsTextures[ADD_BOT_BUTTON_INDEX].second = this->_driver->getTexture("ButtonGFX/addbotbuttonhovered.png")) ||
      !(this->_buttonsTextures[ADD_PLAYER_BUTTON_INDEX].first = this->_driver->getTexture("ButtonGFX/addplayerbutton.png")) ||
      !(this->_buttonsTextures[ADD_PLAYER_BUTTON_INDEX].second = this->_driver->getTexture("ButtonGFX/addplayerbuttonhovered.png")) ||
      !(this->_buttonsTextures[DELETE_PLAYER_BUTTON_INDEX].first = this->_driver->getTexture("ButtonGFX/deleteplayerbutton.png")) ||
      !(this->_buttonsTextures[DELETE_PLAYER_BUTTON_INDEX].second = this->_driver->getTexture("ButtonGFX/deleteplayerbuttonhovered.png")) ||
      !(this->_buttonsTextures[DELETE_BOT_BUTTON_INDEX].first = this->_driver->getTexture("ButtonGFX/deletebotbutton.png")) ||
      !(this->_buttonsTextures[DELETE_BOT_BUTTON_INDEX].second = this->_driver->getTexture("ButtonGFX/deletebotbuttonhovered.png")))
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
  this->_options->setPlayers(this->_players);

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
  this->_buttons.emplace_back(engine->getWindowSize().X - (MenuState::BUTTON_WIDTH - 10),
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 1,
			      engine->getWindowSize().X - 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_DELETE_PLAYER,
			      L"",
			      L"");
  this->_buttons.emplace_back(engine->getWindowSize().X - (MenuState::BUTTON_WIDTH - 10),
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      engine->getWindowSize().X - 10,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 3,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_DELETE_AI,
			      L"",
			      L"");
  this->_buttons.emplace_back(engine->getWindowSize().X  / 2 - MenuState::BUTTON_WIDTH / 2,
			      engine->getWindowSize().Y   - MenuState::BUTTON_HEIGHT - 20,
			      engine->getWindowSize().X / 2  - MenuState::BUTTON_WIDTH / 2 + MenuState::BUTTON_WIDTH ,
			      engine->getWindowSize().Y  - 20,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_PLAY,
			      L"",
			      L"");
  this->_buttons.emplace_back(engine->getWindowSize().X - (MenuState::BUTTON_WIDTH - 10) * 2,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 1,
			      engine->getWindowSize().X - (MenuState::BUTTON_WIDTH - 10),
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_PLAYER,
			      L"",
			      L"");
  this->_buttons.emplace_back(engine->getWindowSize().X - (MenuState::BUTTON_WIDTH - 10) * 2,
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 2,
			      engine->getWindowSize().X - (MenuState::BUTTON_WIDTH - 10),
			      engine->getWindowSize().Y  / 4 + MenuState::BUTTON_HEIGHT * 3,
			      (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_ADD_AI,
			      L"",
			      L"");
  this->_drawButtons();
  this->_buttons[this->_buttons.size() - 5]->setImage(this->_buttonsTextures[DELETE_PLAYER_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 5]->setPressedImage(this->_buttonsTextures[DELETE_PLAYER_BUTTON_INDEX].second);
  this->_buttons[this->_buttons.size() - 4]->setImage(this->_buttonsTextures[DELETE_BOT_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 4]->setPressedImage(this->_buttonsTextures[DELETE_BOT_BUTTON_INDEX].second);
  this->_buttons[this->_buttons.size() - 3]->setImage(this->_buttonsTextures[PLAY_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 3]->setPressedImage(this->_buttonsTextures[PLAY_BUTTON_INDEX].second);
  this->_buttons[this->_buttons.size() - 2]->setImage(this->_buttonsTextures[ADD_PLAYER_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 2]->setPressedImage(this->_buttonsTextures[ADD_PLAYER_BUTTON_INDEX].second);
  this->_buttons.back()->setImage(this->_buttonsTextures[ADD_BOT_BUTTON_INDEX].first);
  this->_buttons.back()->setPressedImage(this->_buttonsTextures[ADD_BOT_BUTTON_INDEX].second);

  engine->getDevice()->setEventReceiver(&this->choosePlayerEventReceiver);
}

void is::ChoosePlayerState::Cleanup(void)
{
  this->eventContext.engine->getDevice()->setEventReceiver(NULL);
}

void is::ChoosePlayerState::Pause(void)
{

}

void is::ChoosePlayerState::Resume(void)
{
  this->eventContext.engine->getDevice()->setEventReceiver(&this->choosePlayerEventReceiver);
  this->_drawButtons();
  this->_buttons[this->_buttons.size() - 5]->setImage(this->_buttonsTextures[DELETE_PLAYER_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 5]->setPressedImage(this->_buttonsTextures[DELETE_PLAYER_BUTTON_INDEX].second);
  this->_buttons[this->_buttons.size() - 4]->setImage(this->_buttonsTextures[DELETE_BOT_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 4]->setPressedImage(this->_buttonsTextures[DELETE_BOT_BUTTON_INDEX].second);
  this->_buttons[this->_buttons.size() - 3]->setImage(this->_buttonsTextures[PLAY_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 3]->setPressedImage(this->_buttonsTextures[PLAY_BUTTON_INDEX].second);
  this->_buttons[this->_buttons.size() - 2]->setImage(this->_buttonsTextures[ADD_PLAYER_BUTTON_INDEX].first);
  this->_buttons[this->_buttons.size() - 2]->setPressedImage(this->_buttonsTextures[ADD_PLAYER_BUTTON_INDEX].second);
  this->_buttons.back()->setImage(this->_buttonsTextures[ADD_BOT_BUTTON_INDEX].first);
  this->_buttons.back()->setPressedImage(this->_buttonsTextures[ADD_BOT_BUTTON_INDEX].second);
  this->_players = this->_options->getPlayers();
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

  if (this->eventContext.stop == true)
    {
      this->eventContext.engine->ChangeState(new GameState);
      return ;
    }
  else if (this->eventContext.chooseSkin == true)
      {
	this->_options->setPlayers(this->_players);
	this->eventContext.chooseSkin = false;
	this->eventContext.engine->PushState(new ChooseSkinState(this->eventContext.player));
	return ;
      }
  this->_driver->beginScene();
  this->_sceneManager->drawAll();
  for (auto b : this->_buttons)
    {
      if (i < 4)
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
		b->setImage(this->_buttonsTextures[VOID_BUTTON_INDEX].first);
		b->setPressedImage(this->_buttonsTextures[VOID_BUTTON_INDEX].second);
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
