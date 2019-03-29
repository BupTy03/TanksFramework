cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TanksFramework)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

add_executable(${PROJECT_NAME} ./src/main.cpp ./src/Game.cpp ./src/GameObject.cpp 
								./src/MovingGameObject.cpp ./src/GameTimer.cpp 
								./src/Wall.cpp ./src/Tank.cpp ./src/Bullet.cpp 
								./src/GameEventsManager.cpp ./src/MainTank.cpp
								./src/EnemyTank.hpp ./src/EnemyTank.cpp)

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system)
