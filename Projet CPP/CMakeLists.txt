cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 11)

project(game)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Game apps/main.cpp src/Game.cpp src/TextureManager.cpp src/Object.cpp src/Map.cpp)
target_link_libraries(Game ${SDL2_LIBRARIES})

target_compile_options(Game PUBLIC -Wall -lSDL2 -lSDL2_image)
