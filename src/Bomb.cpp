//
// Created by vincent on 13/06/17.
//

#include "GameState.hpp"
#include "Bomb.hpp"

unsigned int			is::Bomb::ID = 0;
unsigned int			is::Bomb::TIME_TO_BLOWUP = 2;


is::Bomb::Bomb(is::map &map, irr::video::ITexture *texture, irr::scene::IAnimatedMesh *bombMesh, const irr::core::vector3df &posMap, int power,
	       irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager, is::PowerUpManager &pm, int &nbrOfPlayerBombs) :
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
	_fires(),
	_pm(pm),
	_collision(false),
	_nbrOfPlayerBombs(nbrOfPlayerBombs)
{
  if (!(this->_node = this->_sceneManager.addOctreeSceneNode(bombMesh, 0, 1)))
    throw is::IndieStudioException("Error on loading bomb.");
  this->_node->setPosition(this->_posSpace);
  this->_node->setScale({0.45f * SCALE, 0.45f * SCALE, 0.45f * SCALE});
  this->_map.addObject(Type::BOMB, {(int)posMap.X, (int)posMap.Y, (int)posMap.Z});
  this->_nbrOfPlayerBombs -= 1;
}

is::Bomb::~Bomb()
{
  this->_nbrOfPlayerBombs += 1;
  this->_map.delObject({(int)this->_posMap.X, (int)this->_posMap.Y, (int)this->_posMap.Z});
}


void is::Bomb::draw()
{
  this->_node->render();
}

void is::Bomb::remove()
{
  this->_node->remove();
}

bool is::Bomb::blowUp(std::list<std::shared_ptr<is::Bomb>> bombs)
{
  std::clock_t 		end_clock = std::clock();
  int 			duration = static_cast<int>((std::clock() - _start_clock) / CLOCKS_PER_SEC);

  if (this->_state == BOMB_PLANTED && duration >= TIME_TO_BLOWUP)
    {
      this->_explosion(bombs);
    }
  else if (this->_state == FIRE && duration >= TIME_TO_BLOWUP)
      {
	this->_stopFires();
	return (true);
      }
  return (false);
}

int 			is::Bomb::_reducePower(std::list<std::shared_ptr<is::Bomb>> bombs,
						  irr::core::vector3df pos,
						  int power,
						  const std::function<void(irr::core::vector3df &)> &callback)
{
  int			ret = 0;
  const 		Block *b;

  callback(pos);
  while (this->_map.canIMoove(is::Vector3d(pos.X, pos.Y, pos.Z)) && ret < power)
    {
      callback(pos);
      ret += 1;
    }

  if ((b = this->_map.findBlock({(int)pos.X, (int)pos.Y, (int)pos.Z}))->getType() == is::Type::BREAK)
    {
      this->_blocksToDelete.emplace_back(pos.X, pos.Y, pos.Z);
      ret += 1;
    }
  else if (b->getType() == Type::BOMB)
      {
	ret += 1;
	auto it = std::find_if(bombs.begin(),
			       bombs.end(),
			       [pos](auto bomb) { return pos.X == bomb->getPos().X && pos.Y == bomb->getPos().Y && pos.Z == bomb->getPos().Z; });
	if (it == bombs.end())
	  return (ret);

	std::cout << std::boolalpha << _alreadyBlowUp << std::endl;
	if ((*it)->_alreadyBlowUp == false)
	  (*it)->_explosion(bombs);
      }
  if (b->getType() == Type::POWERUP)
    {
        _pm.getPowerUp({pos.X, pos.Y, pos.Z});
    }
  return (ret);
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

void is::Bomb::_startFires(std::list<std::shared_ptr<is::Bomb>> bombs)
{
  this->_fires.emplace_back(this->_map, &this->_sceneManager, &this->_videoDriver, this->_posSpace, this->_posMap, FireDirection::FORWARD,
                            this->_reducePower(bombs, this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.X += 1;}), &_pm);
  this->_fires.emplace_back(this->_map, &this->_sceneManager, &this->_videoDriver, this->_posSpace, this->_posMap, FireDirection::BACKWARD,
			    this->_reducePower(bombs, this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.X -= 1; }), &_pm);
  this->_fires.emplace_back(this->_map, &this->_sceneManager, &this->_videoDriver, this->_posSpace, this->_posMap, FireDirection::RIGHT,
			    this->_reducePower(bombs, this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.Y += 1; }), &_pm);
  this->_fires.emplace_back(this->_map, &this->_sceneManager, &this->_videoDriver, this->_posSpace, this->_posMap, FireDirection::LEFT,
			    this->_reducePower(bombs, this->_posMap, this->_power, [&](irr::core::vector3df &pos) { pos.Y -= 1; }), &_pm);
  std::for_each(this->_fires.begin(), this->_fires.end(), [](Fire &fire) {
    fire.startFire();
  });
  std::for_each(this->_blocksToDelete.begin(), this->_blocksToDelete.end(), [&](auto pos) {
      this->_map.delObject(pos);
  });
}

void is::Bomb::_stopFires()
{
  std::for_each(this->_fires.begin(), this->_fires.end(), [this](Fire &fire) {
    fire.stopFire(_pm);
  });
}

const irr::core::vector3df &is::Bomb::getPos() const
{
  if (_node)
	  return (this->_node->getPosition());
  return (_posSpace);
}

void			is::Bomb::setPos(irr::core::vector3df const &pos)
{
  _posSpace = pos;
}

void is::Bomb::_explosion(std::list<std::shared_ptr<is::Bomb>> bombs)
{
  this->_alreadyBlowUp = true;
  this->_state = FIRE;
  this->_startFires(bombs);
  this->_start_clock = std::clock();
}

bool is::Bomb::getCollision() const
{
  return _collision;
}

bool is::Bomb::alreadyBlowUp() const
{
  return _alreadyBlowUp;
}

void is::Bomb::setCollision(bool b)
{
	_collision = b;
}

irr::scene::IMeshSceneNode *is::Bomb::getMesh()
{
  return (_node);
}

void is::Bomb::setMesh(irr::scene::IMeshSceneNode *mesh)
{
_node = mesh;
}

const irr::core::vector3df &is::Bomb::getPos2() const
{
  return _posMap;
}
