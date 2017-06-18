//
// Created by vincent on 13/06/17.
//

#ifndef MAP_BOMB_HPP
#define MAP_BOMB_HPP


#include <ITexture.h>
#include <thread>
#include <mutex>
#include "map.hpp"
#include "IndieStudioException.hpp"
#include "Fire.hpp"
#include "map.hpp"
#include "PowerUpManager.hpp"

namespace is
{
  class PowerUpManager;
  class map;
  class Fire;
  class Bomb
  {
   public:

    static unsigned int			ID;
    static unsigned int			TIME_TO_BLOWUP;

    Bomb(map &map, irr::video::ITexture *texture, irr::scene::IAnimatedMesh *bombMesh,
	 const irr::core::vector3df &posMap, int power,
	 irr::video::IVideoDriver &videoDriver, irr::scene::ISceneManager &sceneManager, is::PowerUpManager &pm,
	 int &nbrOfPlayerBombs);

    ~Bomb();

    void 				draw();
    void 				remove();
    bool 				blowUp(std::list<std::shared_ptr<is::Bomb>> bombs);
    const irr::core::vector3df		&getPos() const;
    void				setPos(irr::core::vector3df const &pos);
    const irr::core::vector3df	&getPos2() const;
    bool				getCollision() const;
    bool 				alreadyBlowUp() const;
    void				setCollision(bool b);
    irr::scene::IMeshSceneNode		*getMesh();
    void				setMesh(irr::scene::IMeshSceneNode *);

    bool 				operator==(const Bomb &rhs) const;
    bool 				operator!=(const Bomb &rhs) const;
    Bomb				&operator=(const Bomb &o);


    unsigned int			_id;
   private:

    enum t_state
    {
      BOMB_PLANTED = 0,
      FIRE
    };

    irr::core::vector3df 		_posMap;
    irr::core::vector3df 		_posSpace;
    int 				_power;
    is::map 				&_map;
    irr::video::IVideoDriver 		&_videoDriver;
    irr::scene::ISceneManager 		&_sceneManager;
    irr::scene::IMeshSceneNode 		*_node;
    bool 				_alreadyBlowUp;
    std::clock_t			_start_clock;
    t_state 				_state;
    std::list<Fire>			_fires;
    std::list<Vector3d>			_blocksToDelete;
    is::PowerUpManager &_pm;
    bool				_collision;
    int 				&_nbrOfPlayerBombs;

    int 				_reducePower(std::list<std::shared_ptr<is::Bomb>> bombs,
						    irr::core::vector3df pos,
						    int power,
						    const std::function<void(irr::core::vector3df &)> &callback);
    void				_startFires(std::list<std::shared_ptr<is::Bomb>> bombs);
    void				_stopFires();
    void				_explosion(std::list<std::shared_ptr<is::Bomb>> bombs);
  };
}

#endif //MAP_BOMB_HPP
