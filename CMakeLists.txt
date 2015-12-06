cmake_minimum_required(VERSION 3.3)
project(SpaceInvaders)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        Bullet.cpp
        Bullet.h
        CollisionManager.cpp
        CollisionManager.h
        Alien.cpp
        Alien.h
        Boss.cpp
        Boss.h
        Ship.cpp
        Ship.h
        SoundManager.cpp
        SoundManager.h
        Ufo.cpp
        Ufo.h
        Barrier.cpp
        Barrier.h
        BarrierTile.cpp
        BarrierTile.h)

add_executable(SpaceInvaders ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SpaceInvaders ${SFML_LIBRARIES})
endif()
