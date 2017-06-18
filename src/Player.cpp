//
// Created by vincent on 17/06/17.
//

#include "Player.hpp"

is::Player::~Player()
{

}

is::Player::Player(Player::PlayerType type, const std::string &meshPath) : type(type), meshPath(meshPath)
{

}

is::Player::Player(const Player &other) :
	type(other.type),
	meshPath(other.meshPath)
{

}

is::Player::PlayerType is::Player::getType() const
{
  return type;
}

void is::Player::setType(Player::PlayerType type)
{
  Player::type = type;
}

const std::string &is::Player::getMeshPath() const
{
  return meshPath;
}

void is::Player::setMeshPath(const std::string &meshPath)
{
  Player::meshPath = meshPath;
}
