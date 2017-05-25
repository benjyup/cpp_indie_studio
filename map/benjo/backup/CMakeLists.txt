cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)


set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	        srcs/main.cpp)
set(SRCS_LIB_MAP
		srcs/include/MapIndie.hpp
        srcs/Fire.cpp
        srcs/Fire.hpp
        srcs/include/ObjectMap.hpp
        srcs/include/IObject.hpp
        srcs/MapIndie.cpp
        srcs/ObjectMap.cpp
        srcs/include/Vector3d.hpp
        srcs/Vector3d.cpp
        srcs/PlanetSystem.cpp
        srcs/PlanetSystem.hpp)
		
include_directories(srcs/include .)

include_directories(../../irrlicht-1.8.4/include ../../Interface ../../src/gameEngine)
link_directories(../../irrlicht-1.8.4/lib/Linux ../../irrlicht-1.8.4/lib/Linux/useful)


ADD_LIBRARY(libmapindie ${SRCS_LIB_MAP})
add_executable(map_TEST ${SOURCE_FILES})



target_link_libraries(map_TEST libmapindie Irrlicht.a GL.so libXxf86vm.so libXext.so libX11.so libXcursor.so)
