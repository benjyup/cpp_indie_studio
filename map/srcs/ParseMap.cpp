//
// ParseMap.cpp for indi in /home/rodrigue.rene/Cours/Semestre_4/C++2/cpp_indie_studio/map/flo
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Wed May 24 23:43:13 2017 Rodrigue RENE
// Last update Thu May 25 00:08:50 2017 Rodrigue RENE
//

#include <fstream>
#include <functional>
#include <iostream>
#include "ParseMap.hpp"

is::ParseMap::ParseMap(std::string const &fileName) : _mapFile(fileName)
{
  fillVector();
}

is::ParseMap::~ParseMap()
{
  _theVector.clear();
}

int	is::ParseMap::fillVector()
{
  std::ifstream file;
  std::string   buff;
  int           i = 0;

  file.open(_mapFile);
  if (!file.good())
    return 4;
  int x = 0;
  while (!file.eof())
    {
      getline(file, buff, '\n');
      int max = fillMap2(i, buff);
      if (i == 0)
	_X = max;
      i++;
    }
  _Y = i;
}

int  is::ParseMap::fillMap2(int numLine, std::string const &line)
{
  int i;
  for ( i=0; line[i]!=0; i++)
    _theVector.push_back(line[i] - '0');
  return (i);
}

std::vector<int> &is::ParseMap::getVector()
{
  return (_theVector);
}
