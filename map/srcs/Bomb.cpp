//
// Created by vincent on 13/06/17.
//

#include <include/Game.hpp>
#include "Bomb.hpp"

unsigned int			is::Bomb::ID = 0;


is::Bomb::Bomb(is::map &map, irr::video::ITexture *texture, irr::scene::IAnimatedMesh *bombMesh, const irr::core::vector3df &posMap, int power,
	   irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager) :
	_id(ID++),
	_posMap(posMap),
	_posSpace(posMap.Y * SCALE - SCALE / 2, 0.55 * SCALE, posMap.X * SCALE + SCALE / 2),
	_power(power),
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager),
	_alreadyBlowUp(false)
{
  if (!(this->_node = this->_sceneManager.addAnimatedMeshSceneNode(bombMesh)))
    throw is::IndieStudioException("Error on loading bomb.");
  this->_node->setPosition(this->_posSpace);
  this->_node->setScale({0.5f * SCALE, 0.5f * SCALE, 0.5f * SCALE});
}

is::Bomb::~Bomb()
{
  std::cerr << "~Bomb() id = " << this->_id << std::endl;
}

void is::Bomb::draw()
{
  this->_node->render();
}

void is::Bomb::remove()
{
  this->_node->remove();
}

void is::Bomb::blowUp()
{
  this->_makeFire();
  std::unique_lock<std::mutex> lock(Game::DRAW_MUTEX);
  this->_node->remove();
}

void is::Bomb::_makeFire()
{
  irr::core::vector3df posMap(this->_posMap.X, this->_posMap.Y, this->_posMap.Y);
  Fire fire_forward(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::FORWARD,
		    this->_reducePower(posMap, this->_power, [](irr::core::vector3df &pos) { pos.X += 1; }));

  posMap = irr::core::vector3df(this->_posMap.X, this->_posMap.Y, this->_posMap.Y);
  Fire fire_backward(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::BACKWARD,
		     this->_reducePower(posMap, this->_power, [](irr::core::vector3df &pos) { pos.X -= 1; }));

  posMap = irr::core::vector3df(this->_posMap.X, this->_posMap.Y, this->_posMap.Y);
  Fire fire_right(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::RIGHT,
		  this->_reducePower(posMap, this->_power, [&](irr::core::vector3df &pos) { pos.Z += 1; }));

  posMap = irr::core::vector3df(this->_posMap.X, this->_posMap.Y, this->_posMap.Y);
  Fire fire_left(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::LEFT,
		 this->_reducePower(posMap, this->_power, [&](irr::core::vector3df &pos) { pos.Z -= 1; }));
  std::this_thread::sleep_for(std::chrono::operator""ms(2000));
  std::unique_lock<std::mutex> lock(Game::DRAW_MUTEX);
}

int 			is::Bomb::_reducePower(irr::core::vector3df pos,
						  int power,
						  const std::function<void(irr::core::vector3df &)> &callback)
{
  int			ret = 0;

  callback(pos);
  while (this->_map.canIMoove(is::Vector3d(pos.X, pos.Z, pos.Z)) && ret < power)
    {
      //std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      callback(pos);
      //std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      ret += 1;
    }
  //std::cout << "ret = " << ret << std::endl;
  return ret;
}

is::Bomb		&is::Bomb::operator=(const Bomb &o)
{
  this->_posMap = o._posMap;
  this->_posSpace = o._posSpace;
  this->_power = o._power;
  this->_node = o._node;
}


bool is::Bomb::operator==(const is::Bomb &other) const
{
  std::cout << "operator==" << std::endl;
  return (this == &other);
}

bool is::Bomb::operator!=(const is::Bomb &rhs) const
{
  return !(rhs == *this);
}

