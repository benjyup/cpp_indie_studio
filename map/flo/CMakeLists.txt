cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	main2.cpp
        map.cpp
        Block.cpp
        Vector3d.cpp
        Game.cpp
	ParseMap.cpp
	Bombs.cpp
    	../../src/GameEngine.cpp
        ../../src/GameEngine.hpp
        ../../Interface/IGameEngine.hpp
        ../../src/GameState.cpp
        ../../src/GameState.hpp
        ../../src/Options.cpp
        ../../src/Options.hpp
	../benjo/srcs/Fire.hpp
	../benjo/srcs/Fire.cpp)

set(SOURCE_TEST
        caca.cpp
        map.cpp
        Block.cpp
        Vector3d.cpp
        Game.cpp
	ParseMap.cpp
	Bombs.cpp
    	../../src/GameEngine.cpp
        ../../src/GameEngine.hpp
        ../../Interface/IGameEngine.hpp
        ../../src/GameState.cpp
        ../../src/GameState.hpp
        ../../src/Options.cpp
        ../../src/Options.hpp
	../benjo/srcs/Fire.hpp
	../benjo/srcs/Fire.cpp)


include_directories(../../irrlicht-1.8.4/include ../../Interface ../benjo/srcs ../../src/gameEngine ./)
link_directories(../../irrlicht-1.8.4/lib/Linux ../../irrlicht-1.8.4/lib/Linux/useful)

add_executable(cpp_indie_studio ${SOURCE_FILES})


target_link_libraries(cpp_indie_studio Irrlicht.a GL.so libXxf86vm.so libXext.so libX11.so libXcursor.so -lpthread)
