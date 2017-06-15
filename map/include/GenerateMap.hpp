//
// Created by peixot_b on 15/06/17.
//

#ifndef MAP_GENERATEMAP_HPP
#define MAP_GENERATEMAP_HPP


#include <vector>
#include <string>

class GenerateMap
{
 public:
  GenerateMap(std::string const &fileName);
  virtual ~GenerateMap();

  void			generate();
  void			initMap();
  int			fillMap(std::string const &line);
  unsigned int		genRandNumber(unsigned int min, unsigned int max);
  void			startGeneration();
  void			genRandBorder(unsigned int col);
  unsigned int		nbOfBlock();
  std::vector<int>	&getMap();

 private:
  unsigned int 		_nbBlock;
  std::vector<int>	_map;
  std::string           _mapFile;
  int			_X;
  int			_Y;
};


#endif //MAP_GENERATEMAP_HPP
