cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
        src/GameEngine.cpp src/GameEngine.hpp
        Interface/IGameEngine.hpp
        src/GameState.cpp src/GameState.hpp
        src/Options.cpp src/Options.hpp
        src/MenuState.cpp src/MenuState.hpp
	src/ScoreEnd.cpp src/ScoreEnd.hpp
	src/PauseState.cpp src/PauseState.hpp
        src/Button.cpp src/Button.hpp
        src/MenuEventReceiver.cpp src/MenuEventReceiver.hpp
	src/ScoreEndEventReceiver.cpp src/ScoreEndEventReceiver.hpp
	src/PauseEventReceiver.cpp src/PauseEventReceiver.hpp
        src/IndieStudioException.cpp src/IndieStudioException.hpp
        src/OptionsState.cpp src/OptionsState.hpp
        src/OptionsEventReceiver.cpp src/OptionsEventReceiver.hpp
	src/IntroState.cpp src/IntroState.hpp
	
	map/include/Block.hpp
        map/include/Fire.hpp
        map/include/Camera.hpp
        map/include/Game.hpp
        map/include/map.hpp
        map/include/ParseMap.hpp
        map/include/PlanetSystem.hpp
        map/include/Vector3d.hpp
	map/include/Character.hpp
        map/include/Bomb.hpp
	map/include/BombsManager.hpp
	map/include/GenerateMap.hpp
	map/srcs/BombsManager.cpp
        map/srcs/Block.cpp
        map/srcs/Fire.cpp
	map/srcs/Character.cpp
        map/srcs/GameEventReceiver.cpp
        map/srcs/Camera.cpp
        map/srcs/Game.cpp
        map/srcs/map.cpp
        map/srcs/ParseMap.cpp
        map/srcs/PlanetSystem.cpp
        map/srcs/Vector3d.cpp
        map/srcs/Sound.cpp
        map/srcs/Bomb.cpp
	map/srcs/GenerateMap.cpp
        map/include/Sound.hpp
        map/include/PowerUp.hpp map/srcs/PowerUp.cpp map/srcs/PowerUpManager.cpp map/include/PowerUpManager.hpp
	)

include_directories(irrlicht-1.8.4/include Interface src/gameEngine src/
                    map/include ./irrKlang-64bit-1.5.0/include)

link_directories(irrlicht-1.8.4/lib/Linux/deepinx86_64 irrlicht-1.8.4/lib/Linux/useful
                ./irrKlang-64bit-1.5.0/bin/linux-gcc-64/)

add_executable(cpp_indie_studio ${SOURCE_FILES})

target_link_libraries(cpp_indie_studio Irrlicht.a GL.so libXxf86vm.so libIrrKlang.so libXext.so libX11.so libXcursor.so -lpthread)
