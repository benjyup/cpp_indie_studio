cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES
        src/main.cpp
        src/GameEngine.cpp include/GameEngine.hpp
        Interface/IGameEngine.hpp
        src/Options.cpp include/Options.hpp
        src/MenuState.cpp include/MenuState.hpp
        src/ScoreEnd.cpp include/ScoreEnd.hpp
        src/PauseState.cpp include/PauseState.hpp
        src/Button.cpp include/Button.hpp
        src/MenuEventReceiver.cpp include/MenuEventReceiver.hpp
        src/ScoreEndEventReceiver.cpp include/ScoreEndEventReceiver.hpp
        src/PauseEventReceiver.cpp include/PauseEventReceiver.hpp
        src/IndieStudioException.cpp include/IndieStudioException.hpp
        src/OptionsState.cpp include/OptionsState.hpp
        src/OptionsEventReceiver.cpp include/OptionsEventReceiver.hpp
        src/IntroEventReceiver.cpp include/IntroEventReceiver.hpp
        src/IntroState.cpp include/IntroState.hpp
        src/ChoosePlayerState.cpp

        include/Block.hpp
        include/Fire.hpp
        include/Camera.hpp
        include/GameState.hpp
        include/map.hpp
        include/ParseMap.hpp
        include/PlanetSystem.hpp
        include/Vector3d.hpp
        include/Character.hpp
        include/Bomb.hpp
        include/BombsManager.hpp
        include/GenerateMap.hpp
        src/BombsManager.cpp
        src/Block.cpp
        src/Fire.cpp
        src/Character.cpp
        src/GameEventReceiver.cpp
        src/Camera.cpp
        src/GameState.cpp
        src/map.cpp
        src/ParseMap.cpp
        src/PlanetSystem.cpp
        src/Vector3d.cpp
        src/Sound.cpp
        src/Bomb.cpp
        src/GenerateMap.cpp
        include/Sound.hpp
        include/PowerUp.hpp src/PowerUp.cpp src/PowerUpManager.cpp include/PowerUpManager.hpp
        include/ChoosePlayerState.hpp
        src/ChoosePlayerEventReceiver.cpp include/ChoosePlayerEventReceiver.hpp src/Player.cpp include/Player.hpp)

include_directories(irrlicht-1.8.4/include Interface src/gameEngine src/
        include ./irrKlang-64bit-1.5.0/include)

link_directories(irrlicht-1.8.4/lib/Linux/deepinx86_64 irrlicht-1.8.4/lib/Linux/useful
        ./irrKlang-64bit-1.5.0/bin/linux-gcc-64/)

add_executable(cpp_indie_studio ${SOURCE_FILES})

target_link_libraries(cpp_indie_studio Irrlicht.a GL.so libXxf86vm.so libIrrKlang.so libXext.so libX11.so libXcursor.so -lpthread)

set(RUNTIME /)

install(TARGETS cpp_indie_studio DESTINATION /usr/games/indie_studio)
install(DIRECTORY lib/ DESTINATION /usr/lib
  PATTERN "*.so"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ OWNER_READ OWNER_EXECUTE)
install(DIRECTORY ButtonGFX/ DESTINATION /usr/games/indie_studio/ButtonGFX
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ)
install(DIRECTORY gfx/ DESTINATION /usr/games/indie_studio/gfx
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ)
install(DIRECTORY IA/ DESTINATION /usr/games/indie_studio/IA
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ)
install(DIRECTORY models/ DESTINATION /usr/games/indie_studio/models
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
      GROUP_EXECUTE GROUP_READ)
install(DIRECTORY powersUp/ DESTINATION /usr/games/indie_studio/powersUp
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ)
install(DIRECTORY chef/ DESTINATION /usr/games/indie_studio/chef
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
      GROUP_EXECUTE GROUP_READ)
install(DIRECTORY map/ DESTINATION /usr/games/indie_studio/
  PATTERN "*"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ)
install(DIRECTORY launcher/ DESTINATION /usr/bin/
  PATTERN "cpp_indie_studio"
  PERMISSIONS WORLD_EXECUTE WORLD_WRITE WORLD_READ
  GROUP_EXECUTE GROUP_READ)
