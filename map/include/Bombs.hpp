//
// Bombs.hpp for Indie in /home/rodrigue.rene/Cours/Semestre_4/C++2/cpp_indie_studio/map/flo
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Thu May 25 00:29:34 2017 Rodrigue RENE
// Last update Thu May 25 10:40:44 2017 Rodrigue RENE
//

#include <functional>
#include "map.hpp"

namespace is
{
  class Bombs
  {
    is::map					*_theMap;
    std::function<void (int, int, int, int)>	_laLambadaX;
    int						_seconds;
    int						_SCALE;
    scene::ISceneManager     *_smgr;
    video::IVideoDriver *_driver;
  public:
    Bombs(is::map *theMap, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr);
    ~Bombs();
    void	putBomb(is::Vector3d &pos, int power);
  };
};
