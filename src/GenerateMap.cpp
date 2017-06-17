//
// Created by peixot_b on 15/06/17.
//

#include "GenerateMap.hpp"
#include <iostream>
#include <ctime>
#include <fstream>

is::GenerateMap::GenerateMap(std::string const &fileName)
	: _mapFile(fileName)
{
  _nbBlock = nbOfBlock();
  initMap();
  generate();
}

is::GenerateMap::~GenerateMap()
{
  _map.clear();
}

std::vector<int>	&is::GenerateMap::getMap()
{
  return _map;
}

unsigned int		is::GenerateMap::nbOfBlock()
{
  std::ifstream file;
  std::string   buff;
  unsigned int           i;

  file.open(_mapFile);
  if (!file.good())
    return 1;
  while (!file.eof())
    {
      getline(file, buff, '\n');
      for (i = 0; buff[i]!=0; i++)
	{}
      return (i);
    }
}

void 			is::GenerateMap::initMap()
{
  std::ifstream file;
  std::string   buff;
  int           i = 0;

  file.open(_mapFile);
  if (!file.good())
    return ;
  int x = 0;
  while (!file.eof())
    {
      getline(file, buff, '\n');
      int max = fillMap(buff);
      if (i == 0)
	_X = max;
      i++;
    }
  _Y = i;
}

int			is::GenerateMap::fillMap(std::string const &line)
{
  int i;
  for ( i=0; line[i]!=0; i++)
    _map.push_back(line[i] - '0');
  return (i);
}

unsigned int		is::GenerateMap::genRandNumber(unsigned int min, unsigned int max)
{
  unsigned int randNbr = min + static_cast <unsigned int> (rand()) / (static_cast <unsigned int> (RAND_MAX / max));
  return (randNbr);
}

void			is::GenerateMap::genRandBorder(unsigned int pos)
{
  unsigned int	i;

  i = 1;
  std::cout << pos << std::endl;
  for (int &j : _map)
    {
      if (i == pos)
	j = 1;
      i++;
    }
}

void			is::GenerateMap::startGeneration()
{
  unsigned int	nbrRand;
  unsigned int	i;

  i = 3;
  nbrRand = genRandNumber(4, _nbBlock - 6);
  genRandBorder(_nbBlock + nbrRand);
  nbrRand = genRandNumber(4, _nbBlock - 6);
  genRandBorder(((_nbBlock * _nbBlock) - (_nbBlock * 2)) + nbrRand);
  nbrRand = genRandNumber(4, (_nbBlock - 6));
  genRandBorder((_nbBlock *  nbrRand) + 2);
  nbrRand = genRandNumber(4, (_nbBlock - 6));
  genRandBorder((_nbBlock *  nbrRand) - 1);
  while (i <= 11)
    {
      nbrRand = genRandNumber(4, (_nbBlock - 6));
      genRandBorder((_nbBlock * i) + nbrRand);
      i++;
    }
}

void			is::GenerateMap::generate()
{
  srand(static_cast <unsigned> (time(0)));
  startGeneration();
  startGeneration();
}
