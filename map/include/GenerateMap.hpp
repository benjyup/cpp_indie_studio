//
// Created by peixot_b on 15/06/17.
//

#ifndef MAP_GENERATEMAP_HPP
#define MAP_GENERATEMAP_HPP


#include <vector>

class GenerateMap
{
 public:
  GenerateMap(unsigned int nbBlock);
  virtual ~GenerateMap();

  void			generate();
  void			initMap();
  unsigned int		genRandNumber(unsigned int min, unsigned int max);
  void			genRandBorder(unsigned int col);

  std::vector<int> &getMap();

 private:
  unsigned int 			_nbBlock;
  std::vector<int>	_map;
};


#endif //MAP_GENERATEMAP_HPP
