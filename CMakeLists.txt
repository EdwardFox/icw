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
set(SOURCE_FILES

    lib/Animation.hpp
    lib/Camera.hpp
    lib/Data.hpp
    lib/Game.hpp
    lib/GameObject.hpp
    lib/Grid.hpp
    lib/Map.hpp
    lib/PhysicsContactListener.hpp
    lib/PhysicsSensor.hpp
    lib/ResourceHolder.hpp
    lib/ResourceHolder.inl
    lib/State.hpp
    lib/World.hpp
    lib/interfaces/IActionComponent.hpp
    lib/interfaces/IComponent.hpp
    lib/interfaces/IContactable.hpp
    lib/interfaces/IGraphicsComponent.hpp
    lib/interfaces/IInputComponent.hpp
    lib/interfaces/IMovementComponent.hpp
    lib/interfaces/IPhysicsComponent.hpp
    lib/interfaces/IStateHandlerComponent.hpp
    lib/components/ActionComponent.hpp
    lib/components/AnimationGraphicsComponent.hpp
    lib/components/Box2DPhysicsComponent.hpp
    lib/components/DefaultStateHandlerComponent.hpp
    lib/components/PlayerInputComponent.hpp
    lib/components/PlayerMovementComponent.hpp
    lib/components/SolidColorGraphicsComponent.hpp
    lib/components/ProjectileAIComponent.hpp
    lib/components/TextureGraphicsComponent.hpp

    src/Animation.cpp
    src/Camera.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/Grid.cpp
    src/Main.cpp
    src/Map.cpp
    src/PhysicsContactListener.cpp
    src/PhysicsSensor.cpp
    src/State.cpp
    src/World.cpp
    src/components/ActionComponent.cpp
    src/components/AnimationGraphicsComponent.cpp
    src/components/Box2DPhysicsComponent.cpp
    src/components/DefaultStateHandlerComponent.cpp
    src/components/PlayerInputComponent.cpp
    src/components/PlayerMovementComponent.cpp
    src/components/SolidColorGraphicsComponent.cpp
    src/components/ProjectileAIComponent.cpp
    src/components/TextureGraphicsComponent.cpp
)

# Executable
add_executable(ICW ${SOURCE_FILES})

# Copy resource files
## Maps
configure_file(media/maps/Temple.tmx media/maps/Temple.tmx COPYONLY)

## Textures
configure_file(media/textures/temple.png media/textures/temple.png COPYONLY)
configure_file(media/textures/ruins.png media/textures/ruins.png COPYONLY)
configure_file(media/textures/ror.png media/textures/ror.png COPYONLY)

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
