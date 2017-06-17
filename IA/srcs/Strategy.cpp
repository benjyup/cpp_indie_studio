#include <Strategy.hpp>



is::Strategy::Strategy(luabridge::lua_State	*L, const std::string &fileName, Ia *ia) : _action (luabridge::getGlobal(L, "action"))
{
  _L = L;
  _open = false;
  loadScript(L, fileName);
  _ia = ia;
  
}

is::Strategy::~Strategy()
{

}

void is::Strategy::loadScript(luabridge::lua_State* L, const std::string& scriptFilename)
{

  if (luaL_dofile(_L, "/media/rene_r/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/rene_r/JUNE/IA/cpp_indie_studio/IA/scripts/attack.lua") || lua_pcall(_L, 0, 0, 0))
    {
      _open = true;
      _action = luabridge::getGlobal(_L, "action");

    }
  else
    {
      std::cout << "Error, can't open script!" << std::endl;
    }
}

void is::Strategy::Allo(std::string const &str)
{
  std::cout << str << std::endl;
}
// int is::Strategy::loadScript(STRAT)
// {
//   if (luabridge::luaL_dofile(_action, _name.c_str) == 0) { // script has opened
//     luabridge::LuaRef table = getGlobal(L, tableName.c_str());
//     if (table.isTable()) {
//       if (table["name"].isString()) {
// 	name = table["name"].cast<std::string>();
//       } else {
// 	name = "Null";
//       }

//       if (table["interact"].isFunction()) {
// 	interactFunc = std::make_unique<LuaRef>(table["interact"]);
//       }
//     }
//   } 
// }

void is::Strategy::goToDir(is::Character::DIR)
{

}

void is::Strategy::choseNextDir()
{
}

void is::Strategy::defineDir()
{

}

void is::Strategy::go()
{
  
  if (_open)
    {
      // luabridge::LuaRef toto = luabridge::getGlobal(_L, "action");
      // int x = toto(2);
      // std::cout<<"go   "/*<<toto()*/<<std::endl;
      luabridge::LuaRef sumNumbers = getGlobal(_L, "sumNumbers");
      int result = sumNumbers(5);
      std::cout << "Result:" << result << std::endl;
    }
  else
    std::cerr<<"Script not open"<<std::endl;

  
}

void is::Strategy::move()
{

}
