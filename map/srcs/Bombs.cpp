//
// Bombs.cpp for Indie in /home/rodrigue.rene/Cours/Semestre_4/C++2/cpp_indie_studio/map/flo
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Thu May 25 00:34:31 2017 Rodrigue RENE
// Last update Thu May 25 11:18:00 2017 Rodrigue RENE
//

#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <thread>
#include <unistd.h>
#include "Fire.hpp"
#include "Bombs.hpp"

is::Bombs::Bombs(is::map *theMap, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr) : _theMap(theMap), _seconds(5), _SCALE(140)
{
  _smgr = smgr;
  _driver = driver;
  _laLambadaX = [&](int x, int y,int z, int const power){
    std::cout<<"ATTEND 3                2  111111111111111111111100000000000\n";
    sleep(_seconds);

    //irr::scene::IAnimatedMesh *m = _theMeshs.find("Cube")->second;
    //    _theMap->addObject(Type::FIRE, pos);
    is::Vector3d posBis(x, y);
    is::Vector3d posTer(x, y);
    int i = 0, x2 = x;
    int goX = 0, goX2 = 0;
    bool isOk, isOk2;
    for (int i = 0; i <= (power * 2); i++)
      {
	std::cout<<"here   "<<i<<"   "<< posBis.getX()<<std::endl;
	if ( isOk = _theMap->canIMoove(posBis))
	  {
	    		std::cout<<"here1111   -1"<<std::endl;
	    if ( goX != -1 && isOk)
	      {
		std::cout<<"here1111   0"<<std::endl;
		Fire  *fire = new Fire(_smgr, _driver, irr::core::vector3df((x * _SCALE) - (_SCALE / 2), 0, posBis.getY()* _SCALE + (_SCALE / 2)), TOP,  power);
		std::cout<<"here11111 APRES  "<<std::endl;
	      }
	    else
	      goX = -1;
	  }
	if (isOk2 = _theMap->canIMoove(posTer))
	  {
	    std::cout<<"here2222222 APRES  -1"<<std::endl;
	    if ( goX2 != -1 && isOk2)
	      {
		std::cout<<"here2222222 APRES  0"<<std::endl;
		Fire  *fire = new Fire(_smgr, _driver, irr::core::vector3df((x2 * _SCALE) - (_SCALE / 2), 0, posTer.getY()* _SCALE + (_SCALE / 2)), TOP, power);
		std::cout<<"here2222222 APRES  1"<<std::endl;
	      }
	    else
	      goX2 = -1;
	  }

	std::cout<<"APRES  "<<33<<"   "<<
	  std::endl;
	posBis.setX(posBis.getX() + 1);
	posTer.setX(posTer.getX() - 1);
	x++;
	x2--;
	usleep(300000);
      }
  };

}

is::Bombs::~Bombs()
{

}

void	is::Bombs::putBomb(is::Vector3d &pos, int power)
{
  std::thread first(this->_laLambadaX, pos.getX(), pos.getY(), pos.getZ(), power);
  first.detach();

  std::cout<<"AFTER\n";
}
