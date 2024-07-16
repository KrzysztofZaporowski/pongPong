cmake_minimum_required(VERSION 3.10)
project(pongPong)

set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "C:\\SFML\\SFML-2.6.1")

include_directories(${SFML_ROOT}/include)

link_directories(${SFML_ROOT}/lib)


add_executable(pongPong main.cpp
        Player.cpp
        Player.h
        GameControler.cpp
        GameControler.h
        Ball.cpp
        Ball.h
)

target_link_libraries(pongPong
        sfml-graphics
        sfml-window
        sfml-system
)

