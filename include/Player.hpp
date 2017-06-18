//
// Created by vincent on 17/06/17.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
#define CPP_INDIE_STUDIO_PLAYER_HPP


#include <iosfwd>
#include <sstream>

namespace is
{

  class Player
  {
   public:

    enum PlayerType : int
    {
      PLAYER,
      AI,
      VOID
    };

    Player(PlayerType type, const std::string &meshPath);
    Player(const Player &other);

    ~Player();

    PlayerType getType() const;

    void setType(PlayerType type);

    const std::string &getMeshPath() const;

    void setMeshPath(const std::string &meshPath);

   private:
    PlayerType 		type;
    std::string		meshPath;
  };

}

#endif //CPP_INDIE_STUDIO_PLAYER_HPP
