cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/GameEngine.cpp src/GameEngine.hpp
        Interface/IGameEngine.hpp
        src/GameState.cpp src/GameState.hpp
        src/Options.cpp src/Options.hpp
        src/MenuState.cpp src/MenuState.hpp
        src/Button.cpp src/Button.hpp
        src/MenuEventReceiver.cpp src/MenuEventReceiver.hpp
        src/IndieStudioException.cpp src/IndieStudioException.hpp
        src/OptionsState.cpp src/OptionsState.hpp
        src/OptionsEventReceiver.cpp src/OptionsEventReceiver.hpp)

include_directories(irrlicht-1.8.4/include Interface src/gameEngine map/include)
link_directories(irrlicht-1.8.4/lib/Linux irrlicht-1.8.4/lib/Linux/useful)

add_executable(cpp_indie_studio ${SOURCE_FILES})

target_link_libraries(cpp_indie_studio Irrlicht.a GL.so libXxf86vm.so libXext.so libX11.so libXcursor.so )
