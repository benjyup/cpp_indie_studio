//
// Created by rene_r on 6/13/17.
//

#include "Ia.hpp"
#include "Strategy.hpp"

is::Ia *robot;

is::Ia::Ia(scene::IAnimatedMesh *node, video::ITexture *texture, scene::ISceneManager *smgr,
	   core::vector3df const &pos, const GameEventReceiver &receiver, const Options &opt,
	   BombsManager &bombsManager) : Character(node, texture, smgr, pos, receiver,opt,bombsManager)
{

  construct_L();

  Strategy *attack = new Strategy(_L, "attack.lua", this);

  //  Strategy *hide   = new Strategy(_L, "hide.lua");
  _theStrats.push_back(attack);
  // _theStrats.push_back(hide);
  // std::cout<<"IA"<<i++<<"\n";
  _isIa = true;
  robot = this;
}

is::Ia::~Ia()
{
  while (!_theStrats.empty())
    _theStrats.pop_back();
}

void printMessage(const std::string& s)
{
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<s << std::endl;
  robot->Allo("YO");
}


void is::Ia::construct_L()
{
  _L = luabridge::luaL_newstate();

  luabridge::luaL_openlibs(_L);
  luabridge::getGlobalNamespace(_L) .addFunction("printMessage", printMessage);
    // .beginClass<Strategy>("Ia")
    // //    .addConstructor<void(*)(luabridge::lua_State	*, const std::string &)>()
    // //    .addProperty("type", &Strategy::getType, &Strategy::setType)
    // .addFunction("Allo", &Ia::Allo)
    // .endClass();
  //  std::cout<<"L"<<i++<<"\n";
}

bool		is::Ia::isInDanger()
{
  return true;
}

void		is::Ia::hideHilself()
{
  
}

irr::core::vector3df	is::Ia::findPlaceForBomb()
{

}

void is::Ia::Allo(std::string const &str)
{
  
  std::cout << "je suis la pour conpliqur les vies" << std::endl;
}


irr::core::vector3df     is::Ia::findEnnemy()
{

}

irr::core::vector3df	is::Ia::findPowerUp()
{

}

void		is::Ia::move()
{
  if (isInDanger())
    _theStrats[0]->go();
  std::cout<<"moveIa\n";
}

void		is::Ia::changeDir(DIR)
{

}