//
// ParseMap.hpp for indi in /home/rodrigue.rene/Cours/Semestre_4/C++2/cpp_indie_studio/map/flo
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Wed May 24 23:41:00 2017 Rodrigue RENE
// Last update Thu May 25 00:13:46 2017 Rodrigue RENE
//

#pragma once

#include <vector>
#include <string>
#include "ParseMap.hpp"
namespace is
{
  class ParseMap
  {
    std::vector<int>      _theVector;
    std::string           _mapFile;
    int			  _X, _Y;

  public:
    ParseMap(std::string const &);
    ~ParseMap();
    
    int			fillMap2(int numLine, std::string const &line);
    std::vector<int>   &getVector();
    int			fillVector();
  };
};
