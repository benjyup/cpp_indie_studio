cmake_minimum_required(VERSION 3.5)
project(map)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        include/Block.hpp
        include/Bombs.hpp
        include/Fire.hpp
        include/Camera.hpp
        include/Game.hpp
        include/map.hpp
        include/ParseMap.hpp
        include/PlanetSystem.hpp
        include/Vector3d.hpp
        srcs/Character.cpp
        srcs/Block.cpp
        srcs/Bombs.cpp
        srcs/Fire.cpp
        srcs/GameEventReceiver.cpp
        srcs/Camera.cpp
        srcs/Game.cpp
        srcs/main.cpp
        srcs/map.cpp
        srcs/ParseMap.cpp
        srcs/PlanetSystem.cpp
        srcs/Vector3d.cpp
        srcs/Sound.cpp
        srcs/BombsT.cpp
        srcs/BombsT.hpp
        include/Sound.hpp
        ../src/GameEngine.cpp
        ../src/GameState.cpp
        ../src/Options.cpp
        ../src/Options.hpp
        ../src/IndieStudioException.cpp
        include/PowerUp.hpp srcs/PowerUp.cpp)

include_directories(../irrlicht-1.8.4/include ../src/ ../Interface ./
                    ./include ../irrKlang-64bit-1.5.0/include)

link_directories(../irrlicht-1.8.4/lib/Linux/deepinx86_64 ../irrlicht-1.8.4/lib/Linux/useful
                ../irrKlang-64bit-1.5.0/bin/linux-gcc-64/)

add_executable(cpp_indie_studio ${SOURCE_FILES})

target_link_libraries(cpp_indie_studio Irrlicht.a GL.so libXxf86vm.so libIrrKlang.so libXext.so libX11.so libXcursor.so -lpthread)
