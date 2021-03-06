//
// Created by kyxo on 5/30/17.
//

#include "Character.hpp"

is::Character::Character(irr::scene::IAnimatedMesh *node, irr::video::ITexture *texture,
			 irr::scene::ISceneManager * smgr,
			 irr::core::vector3df const & pos,
			 const GameEventReceiver &receiver,
			 std::map<Options::MOVES, irr::EKEY_CODE> const &Config,
			 BombsManager &bombsManager, int id)
	: _mesh(smgr->addAnimatedMeshSceneNode(node)), _text(texture), _smgr(smgr), _pos(pos), _speed(DEFAULT_SPEED), _bomb(DEFAULT_BOMB), _power(DEFAULT_POWER),
	  _receiver(receiver),
	  _bombsManager(bombsManager),
	  _keySlow(false),
	  _Config(Config),
	  _animDie(0),
	  _id(id)
{
  irr::scene::ITriangleSelector	*t;
  if (_mesh)
    {
      _mesh->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      _mesh->setMD2Animation(irr::scene::EMAT_RUN);
      _mesh->setScale(irr::core::vector3df(1, 1, 1));
      _mesh->setMaterialTexture(0, _text);
      _mesh->setPosition(pos);
      _dir = Character::DIR::TOP;
      _mesh->setRotation(irr::core::vector3df(0, 270, 0));
      _mesh->getMaterial(0).Lighting = true;
      _mesh->setScale({0.26f, 0.26f, 0.26f});
      _mesh->getMaterial(0).NormalizeNormals = true;
      t = smgr->createTriangleSelector(_mesh);
      _mesh->setTriangleSelector(t);
      t->drop();
    }
  _state = STATE::ALIVE;
}

void		is::Character::die()
{
  _mesh->remove();
}

void		is::Character::moove()
{
  irr::core::vector3df v = _mesh->getPosition();
  bool			t = false;

  if (_state == STATE::DYING)
    return;
  if (_receiver.isKeyDown(_Config.at(Options::MOVES::MOVE_UP)) || _receiver.isVerAxe((Button::GUI_ID_BOUTON)_id) == 1)
    {
      if (_dir != is::Character::DIR::TOP)
	{
	  _mesh->setMD2Animation(irr::scene::EMAT_RUN);
	  _mesh->setRotation(irr::core::vector3df(0, 270, 0));
	  _dir = is::Character::DIR::TOP;
	}
      _mesh->setPosition(irr::core::vector3df(v.X, v.Y, v.Z + DEFAULT_SPEED + _speed));
      t = true;
    }
  if (_receiver.isKeyDown(_Config.at(Options::MOVES::MOVE_DOWN)) || _receiver.isVerAxe((Button::GUI_ID_BOUTON)_id) == -1)
    {
      if (_dir != is::Character::DIR::DOWN)
	{
	  _mesh->setMD2Animation(irr::scene::EMAT_RUN);
	  _mesh->setRotation(irr::core::vector3df(0, 90, 0));
	  _dir = is::Character::DIR::DOWN;
	}
      _mesh->setPosition(irr::core::vector3df(v.X, v.Y, v.Z - DEFAULT_SPEED - _speed));
      t = true;
    }
  if (_receiver.isKeyDown(_Config.at(Options::MOVES::MOVE_RIGHT)) || _receiver.isHorAxe((Button::GUI_ID_BOUTON)_id) == 1)
    {
      if (_dir != is::Character::DIR::RIGHT)
	{
	  _mesh->setMD2Animation(irr::scene::EMAT_RUN);
	  _mesh->setRotation(irr::core::vector3df(0, 0, 0));
	  _dir = is::Character::DIR::RIGHT;
	}
      _mesh->setPosition(irr::core::vector3df(v.X + DEFAULT_SPEED + _speed, v.Y, v.Z));
      t = true;
    }
  if (_receiver.isKeyDown(_Config.at(Options::MOVES::MOVE_LEFT)) || _receiver.isHorAxe((Button::GUI_ID_BOUTON)_id) == -1)
    {
      if (_dir != is::Character::DIR::LEFT)
	{
	  _mesh->setMD2Animation(irr::scene::EMAT_RUN);
	  _mesh->setRotation(irr::core::vector3df(0, 180, 0));
	  _dir = is::Character::DIR::LEFT;
	}
      _mesh->setPosition(irr::core::vector3df(v.X - DEFAULT_SPEED - _speed, v.Y, v.Z));
      t = true;
    }
  if (_receiver.isKeyDown(_Config.at(Options::MOVES::MOVE_ACTION)) || _receiver.isActionOn((Button::GUI_ID_BOUTON)_id))
    {
      _dir = DIR::NONE;
      if (_keySlow && this->_bomb > 0)
	{
	  _mesh->setMD2Animation(irr::scene::EMAT_CROUCH_WALK);
	  _bombsManager.putBomb({ceil(floor(_mesh->getPosition().Z) / (float) SCALE) - 1,
				 ceil(floor(_mesh->getPosition().X) / (float) SCALE), 0},
				this->_power, this->_bomb);
	}
      _keySlow = false;
      t = true;
    }
  if (!t)
  {
    if (_dir != is::Character::DIR::NONE)
      _mesh->setMD2Animation(irr::scene::EMAT_STAND);
    _dir = DIR::NONE;
    _keySlow = true;
  }
}

void is::Character::update(is::PowerUpManager *pm, is::map *map) {
  irr::core::vector3df pos = {(irr::f32) (ceil(floor(_mesh->getPosition().Z) / (float)SCALE) - 1), ceil(floor(_mesh->getPosition().X) / (float)SCALE), 0};
  int ret = map->getLocalType({static_cast<int32_t>(ceil(floor(_mesh->getPosition().Z) / (float)SCALE) - 1),
                               static_cast<int32_t>(ceil(floor(_mesh->getPosition().X) / (float)SCALE)), 0});

  if (ret == is::POWERUP)
    {
      pm->getPower(*this, pos);
      pm->getPowerUp(pos);
    }
  else if (ret == is::FIRE)
      {
	if (_state != STATE::DYING)
	    _mesh->setMD2Animation(irr::scene::EMAT_CROUCH_DEATH);
	_state = STATE::DYING;
      }
  if (_state == STATE::DYING)
    {
      if (_mesh->getFrameNr() >= (float)_mesh->getEndFrame() - 1.0f)
	 _animDie++;
      if (_animDie == 5)
	  _state = STATE::DEAD;
    }
}

irr::scene::ISceneNode 		*is::Character::getMesh()
{
  return (_mesh);
}

bool 					is::Character::getAlive()
{
  return !(_state == STATE::DEAD);
}

void is::Character::incSpeed() {
    _speed += 0.1;
}

void is::Character::incbomb() {
    _bomb += 1;
}

void is::Character::incPower() {
    _power += 1;
}

irr::core::vector3df const &is::Character::getPos() const
{
  return _mesh->getPosition();
}

void is::Character::pushAnim(irr::scene::ISceneNodeAnimator *anim	, unsigned int id)
{
  _anim[id] = anim;
}

irr::scene::ISceneNodeAnimator *is::Character::getAnim(unsigned int _id)
{
  return _anim[_id];
}

float                             is::Character::getSpeed() const
{
  return (this->_speed);
}
int                             is::Character::getBomb() const
{
  return (this->_bomb);
}

int                             is::Character::getPower() const
{
  return (this->_power);
}

int                             is::Character::getId()
{
  return _id;
}