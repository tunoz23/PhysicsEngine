cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# ─── Third‐Party Libraries You Already Have ───────────────────────────────────────────
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)
# …(other thirdparty dependencies you had)…

#
# ─── JOLT PHYSICS (use the “Build” subfolder) ────────────────────────────────────────
#
# 1) If you want to enable asserts or SIMD inside Jolt, set these BEFORE
#    Jolt’s CMake runs. Otherwise defaults apply.
option(JPH_ENABLE_ASSERTS   "Enable Jolt internal assertions"       ON)
option(JPH_ENABLE_SIMD      "Compile Jolt with SIMD optimizations" ON)
option(JPH_BUILD_TESTS      "Build Jolt’s unit tests"              OFF)

# 2) Point add_subdirectory() at JoltPhysics/Build (where Jolt’s CMakeLists.txt lives)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/JoltPhysics/Build
    ${CMAKE_CURRENT_BINARY_DIR}/JoltPhysicsBuild
)
#
# After this, CMake will expose at least one target named “Jolt” (and maybe “JoltBuildSettings”).
# You can verify the exact library‐target name in CMake’s configure output. Usually it’s “Jolt”.
#

#
# ─── Your Executable Target ──────────────────────────────────────────────────────────
#
add_executable(${PROJECT_NAME}
    src/main.cpp
    thirdparty/glad/glad.c

    #<------------- your own headers ------------->
    src/headers/Systems/RenderSystem.h
    src/headers/Systems/WindowSystem.h
    src/headers/Systems/PhysicsSystem.h   # this will #include <Jolt/…> now
    src/headers/Systems/CollisionSystem.h
    src/headers/Systems/CameraSystem.h

    src/headers/Components/MeshComponent.h
    src/headers/Components/PhysicsComponent.h
    src/headers/Components/RigidBodyComponent.h
    src/headers/Components/TransformComponent.h
    src/headers/Components/CameraComponent.h

    src/headers/Circle.h
    src/headers/Rectangle.h
    src/headers/Cube.h
    src/headers/Sphere.h

    src/headers/ActiveCameraData.h

    src/headers/Components/ColliderComponents/CircleColliderComponent.h
    src/headers/Components/ColliderComponents/OBBColliderComponent.h

    src/headers/Events/CollisionEvent.h
    src/headers/Events/WallCollisionEvent.h
    src/headers/Events/OBBCollisionEvent.h

    src/headers/Scene.h
    src/headers/Vertex.h

    #<------------- your own .cpp files ------------->
    src/Scene.cpp
    src/Systems/RenderSystem.cpp
    src/Systems/WindowSystem.cpp
    src/Systems/PhysicsSystem.cpp   # implements the EnTT ↔ Jolt bridge
    src/Systems/CollisionSystem.cpp
    src/Systems/CameraSystem.cpp

    src/Shapes/Circle.cpp
    src/Shapes/Rectangle.cpp
    src/Shapes/Cube.cpp
    src/Shapes/Sphere.cpp
)

#
# ─── Include Directories ────────────────────────────────────────────────────────────
#
target_include_directories(${PROJECT_NAME} PUBLIC
    # Your project’s include folders:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Components/ColliderComponents
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Systems

    # Third‐party you already had:
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/entt

    # ─── Jolt’s include folders: ─────────────────────────────────────────────
    #   We know Jolt’s source tree is one level up from “Build/”, so its headers
    #   live under ../Core, ../Physics, ../Collision, etc.
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/JoltPhysics/Jolt
#    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/JoltPhysics/Physics
#    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/JoltPhysics/Collision
    #   (If Jolt has any other top‐level folders with headers, add them here too.)
)

#
# ─── Link Libraries ────────────────────────────────────────────────────────────────
#
target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCE_PATH="${CMAKE_SOURCE_DIR}/Resources/")

target_link_libraries(${PROJECT_NAME} PRIVATE
    glm
    glfw
    Jolt      # ← This is the library target Jolt’s CMakeLists created for you
)

# (Optionally, if you see a target called JoltBuildSettings or Jolt-physics or similar,
#  you can inspect CMake’s configure output to confirm the exact name. Usually “Jolt” is correct.)
