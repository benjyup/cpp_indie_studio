//
// IObjrct.hpp for indie in /home/rodrigue.rene/TEST/DEPOT/cpp_indie_studio/map
// 
// Made by Rodrigue RENE
// Login   <rodrigue.rene@epitech.net>
// 
// Started on  Sun May 21 00:49:11 2017 Rodrigue RENE
// Last update Sun May 21 15:08:57 2017 Rodrigue RENE
//

#pragma once

#include "Vector3d.hpp"

namespace Indie
{

  enum TYPEOBJECT
  {
    UNDEFINED,
    BLOCK,
    FIRE,
    PERSO,
    POWERUP,
    BOMB,
    BREAKABLE
  };
  
  class IObject
  {
   public:
    virtual ~IObject(void) {};

    virtual void                        setName(std::string const &) = 0;
    virtual void                        setPosition(Indie::Vector3d const &) = 0;
    virtual void                        setPosition(int,int,int) = 0;

    virtual std::string const &         getName(void) const = 0;
    virtual Indie::TYPEOBJECT		getType() const = 0;
    virtual Indie::Vector3d const &	getPosition (void) const = 0;
    virtual void			changeType(Indie::TYPEOBJECT) = 0;
    virtual void			burn() = 0;

  };
}
