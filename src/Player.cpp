//
// Created by vincent on 17/06/17.
//

#include "Player.hpp"

Player::~Player()
{

}

Player::Player(Player::PlayerType type, const std::string &meshPath) : type(type), meshPath(meshPath)
{

}

Player::Player(const Player &other) :
	type(other.type),
	meshPath(other.meshPath)
{

}

Player::PlayerType Player::getType() const
{
  return type;
}

void Player::setType(Player::PlayerType type)
{
  Player::type = type;
}

const std::string &Player::getMeshPath() const
{
  return meshPath;
}

void Player::setMeshPath(const std::string &meshPath)
{
  Player::meshPath = meshPath;
}
