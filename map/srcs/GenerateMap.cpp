//
// Created by peixot_b on 15/06/17.
//

#include "GenerateMap.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

GenerateMap::GenerateMap(unsigned nbBlock) : _nbBlock(nbBlock)
{
  initMap();
  generate();
}

GenerateMap::~GenerateMap()
{
  _map.clear();
}

std::vector<int> &GenerateMap::getMap()
{
  return _map;
}

void GenerateMap::initMap()
{
  unsigned int	i;
  unsigned int	j;

  i = 1;
  j = 1;
  while (i <= _nbBlock * _nbBlock)
    {
      if (i == 1 || i == (_nbBlock * _nbBlock) - _nbBlock + 1)
	{
	  while (j <= _nbBlock)
	    {
	      _map.push_back(1);
	      j++;
	      i++;
	    }
	}
      else
	{
	  _map.push_back(1);
	  while (j <= _nbBlock - 2)
	    {
	      _map.push_back(0);
	      j++;
	      i++;
	    }
	  _map.push_back(1);
	  i+= 2;
	}
      j = 1;
    }
  std::cout << "NOMBRE PUSH VECT" << i << std::endl;
}



unsigned int GenerateMap::genRandNumber(unsigned int min, unsigned int max)
{
  unsigned int randNbr = min + static_cast <unsigned int> (rand()) / (static_cast <unsigned > (RAND_MAX / max));
  return (randNbr);
}

void GenerateMap::genRandBorder(unsigned int pos)
{
//  unsigned int	nbrRand;
//  unsigned int	i;
//
//  i = 1;
//  std::cout << pos << std::endl;
//  for (int &j : _map)
//    {
//      if (i == pos)
//	j = 1;
//      i++;
//    }
}

void GenerateMap::generate()
{
  //srand(static_cast <unsigned> (time(0)));

//  unsigned int	nbrRand;
//  nbrRand = genRandNumber(4, _nbBlock - 5);
//  genRandBorder(_nbBlock + nbrRand);
//  nbrRand = genRandNumber(4, _nbBlock - 5);
//  genRandBorder(((_nbBlock * _nbBlock) - (_nbBlock * 2)) + nbrRand);


//  unsigned int	nbrRand;
//  unsigned int	i;
//  i = 1;
//  nbrRand = genRandNumber(3, _nbBlock - 5);
//  for (int &j : _map)
//    {
//      if (i == _nbBlock + nbrRand)
//	j = 1;
//      i++;
//    }
//  i = 1;
//  nbrRand = genRandNumber(3, _nbBlock - 5);
//  for (int &k : _map)
//    {
//      if (i == (((_nbBlock * _nbBlock) - (_nbBlock * 2)) + nbrRand))
//	{
//	  k = 1;
//	}
//      i++;
//    }
}