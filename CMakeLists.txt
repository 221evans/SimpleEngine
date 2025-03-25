cmake_minimum_required(VERSION 3.30)
project(SimpleEngine)

set(CMAKE_CXX_STANDARD 26)
# Find and Include Raylib
find_package(raylib REQUIRED)
include_directories(${RAYLIB_INCLUDE_DIRS})

if (NOT raylib_FOUND)
    # This is a fallback if you don't have raylib installed system-wide
    # It will fetch raylib from the repository and build it
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        include_directories(${raylib_SOURCE_DIR}/src)  # <---
        link_directories(${raylib_SOURCE_DIR}/src)  # <---

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif()




add_executable(SimpleEngine main.cpp
        src/TextureHandler.cpp
        src/TextureHandler.hpp
        src/Game.cpp
        src/Game.hpp
        src/Entity/Entity.cpp
        src/Entity/Entity.hpp
        src/Entity/Component.hpp
        src/Entity/SpriteComponent.cpp
        src/Entity/SpriteComponent.hpp
        src/Entity/CombatComponent.cpp
        src/Entity/CombatComponent.hpp
        src/Entity/PlayerEntity.cpp
        src/Entity/PlayerEntity.hpp
        src/Entity/EnemyEntity.cpp
        src/Entity/EnemyEntity.hpp)
target_link_libraries(SimpleEngine PRIVATE raylib)