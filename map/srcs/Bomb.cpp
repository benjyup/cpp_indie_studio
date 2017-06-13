//
// Created by vincent on 13/06/17.
//

#include <map.hpp>
#include <IndieStudioException.hpp>
#include <thread>
#include "Bomb.hpp"

is::Bomb::Bomb(is::map &map, irr::video::ITexture *texture, irr::scene::IAnimatedMesh *bombMesh, const irr::core::vector3df &posMap, int power,
	   irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager) :
	_posMap(posMap),
	_posSpace(posMap.Y * SCALE - SCALE / 2, 0.55 * SCALE, posMap.X * SCALE + SCALE / 2),
	_power(power),
	_map(map),
	_videoDriver(videoDriver),
	_sceneManager(sceneManager)
{
  if (!(this->_node = this->_sceneManager.addAnimatedMeshSceneNode(bombMesh)))
    throw is::IndieStudioException("Error on loading bomb.");
  this->_node->setPosition(this->_posSpace);
  this->_node->setScale({0.5f * SCALE, 0.5f * SCALE, 0.5f * SCALE});
}

is::Bomb::~Bomb()
{

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
  std::cout << "power = " << this->_power << std::endl;
  irr::core::vector3df posMap(this->_posMap.X, this->_posMap.Y, this->_posMap.Y);
  Fire fire_forward(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::FORWARD,
		    this->reducePower(posMap, this->_power, [](irr::core::vector3df &pos) {pos.X += 1;}));
  Fire fire_backward(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::BACKWARD,
		     this->reducePower(posMap, this->_power, [](irr::core::vector3df &pos) {pos.X -= 1;}));

  posMap = irr::core::vector3df(this->_posMap.X, this->_posMap.Y, this->_posMap.Y);
  Fire fire_right(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::RIGHT,
		  this->reducePower(posMap, this->_power, [&](irr::core::vector3df &pos) {pos.Z += 1;}));

  Fire fire_left(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::LEFT,
		 this->reducePower(posMap, this->_power, [&](irr::core::vector3df &pos) {pos.Z -= 1;}));
  std::this_thread::sleep_for(std::chrono::operator""ms(2000));
  this->_node->remove();
}

int 			is::Bomb::reducePower(irr::core::vector3df pos,
						  int power,
						  const std::function<void(irr::core::vector3df &)> &callback)
{
  int			ret = 0;

  callback(pos);
  while (this->_map.canIMoove2(is::Vector3d(pos.X, pos.Z, pos.Z)) && ret < power)
    {
      std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      callback(pos);
      std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
      ret += 1;
    }
  std::cout << "ret = " << ret << std::endl;
  return ret;
}

