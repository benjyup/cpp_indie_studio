//
// Created by vincent on 13/06/17.
//

#include "Game.hpp"
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
	_alreadyBlowUp(false),
	_start_clock(std::clock()),
	_state(BOMB_PLANTED),
	_fires()
{
  if (!(this->_node = this->_sceneManager.addAnimatedMeshSceneNode(bombMesh)))
    throw is::IndieStudioException("Error on loading bomb.");
  this->_node->setPosition(this->_posSpace);
  this->_node->setScale({0.5f * SCALE, 0.5f * SCALE, 0.5f * SCALE});
  std::cerr << "Bomb() id = " << this->_id << std::endl;
  std::cout << "Bomb pos.x = " << posMap.X << " pos.y = " << posMap.Y << " pos.Z = " << posMap.Z << std::endl;
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

bool is::Bomb::blowUp()
{
  std::clock_t 		end_clock = std::clock();
  int 			duration = static_cast<int>((std::clock() - _start_clock) / CLOCKS_PER_SEC);


  if (this->_state == BOMB_PLANTED && duration == ((_id == 0) ? (2) : (5)))
    {
      this->_state = FIRE;
      this->_startFires();
      this->_node->remove();
      this->_start_clock = std::clock();
    }
  else if (this->_state == FIRE && duration == 2)
      {
	this->_stopFires();
	return (true);
      }
  return (false);
}

int 			is::Bomb::_reducePower(irr::core::vector3df pos,
						  int power,
						  const std::function<void(irr::core::vector3df &)> &callback)
{
  int			ret = 0;

  std::cerr << "_reducPower" << std::endl;
  callback(pos);
  std::cout << "pos.x = " << pos.X << " pos.y = " << pos.Y << " pos.z = " << pos.Z<< std::endl;
  while (this->_map.canIMoove(is::Vector3d(pos.X, pos.Y, pos.Z)) && ret < power)
    {
      callback(pos);
      ret += 1;
    }
  const Block *b;
  if ((b = this->_map.findBlock({pos.X, pos.Y, pos.Z}))->getType() == is::Type::BREAK)
    this->_blocksToDelete.emplace_back(pos.X, pos.Y, pos.Z);

  std::cout << "ret = " << ret << std::endl;
  std::cerr << "_reducPower" << std::endl;
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
  return (this == &other);
}

bool is::Bomb::operator!=(const is::Bomb &rhs) const
{
  return !(rhs == *this);
}

void is::Bomb::_startFires()
{
  this->_fires.emplace_back(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::FORWARD,
			    this->_reducePower(this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.X += 1; }));
  this->_fires.emplace_back(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::BACKWARD,
			    this->_reducePower(this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.X -= 1; }));
  this->_fires.emplace_back(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::RIGHT,
			    this->_reducePower(this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.Y += 1; }));
  this->_fires.emplace_back(&this->_sceneManager, &this->_videoDriver, this->_posSpace, FireDirection::LEFT,
			    this->_reducePower(this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.Y -= 1; }));
  std::for_each(this->_fires.begin(), this->_fires.end(), [](Fire &fire) {
    fire.startFire();
  });
  std::for_each(this->_blocksToDelete.begin(), this->_blocksToDelete.end(), [&](auto pos) {
    this->_map.delObject(pos);
  });
}

void is::Bomb::_stopFires()
{
  std::for_each(this->_fires.begin(), this->_fires.end(), [](Fire &fire) {
    fire.stopFire();
  });
}
