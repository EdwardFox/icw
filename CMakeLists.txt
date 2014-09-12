# CMAKE minimum
cmake_minimum_required(VERSION 2.8.4)

# Project name
project(ICW)

# Version
set(ICW_VERSION_MAJOR 0)
set(ICW_VERSION_MINOR 1)

# CXX Flags
add_definitions(-g -Wall -std=c++11)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files
set(SOURCE_FILES src/Main.cpp src/Game.cpp src/GameObject.cpp src/Grid.cpp src/World.cpp src/components/SolidColorGraphicsComponent.cpp src/components/TextureGraphicsComponent.cpp src/components/AnimationGraphicsComponent.cpp src/components/Box2DPhysicsComponent.cpp src/components/TestAIComponent.cpp src/components/PlayerInputComponent.cpp src/Animation.cpp src/components/PlayerStateHandlerComponent.cpp src/State.cpp src/PhysicsGroundContactListener.cpp src/components/PlayerMovementComponent.cpp)

# Executable
add_executable(ICW ${SOURCE_FILES})

# Copy resource files
configure_file(media/textures/DefaultTile.png media/textures/DefaultTile.png COPYONLY)
configure_file(media/textures/DefaultAnimation.png media/textures/DefaultAnimation.png COPYONLY)

# Detect and add cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Find any version 2.X of SFML
# See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# Find any version of Box2D
# See the FindBox2d.cmake file for additional details and instructions
find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
  include_directories(${BOX2D_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARIES})
endif()
