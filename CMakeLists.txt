cmake_minimum_required(VERSION 3.10)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)

add_executable(${CMAKE_PROJECT_NAME} 
    src/main.cpp
    thirdparty/glad/glad.c
        src/headers/Scene.h
        src/Scene.cpp
        src/headers/MeshComponent.h
        src/headers/RenderSystem.h
        src/RenderSystem.cpp
        src/WindowSystem.cpp
        src/headers/WindowSystem.h
        src/headers/TransformComponent.h
        src/PhysicsSystem.cpp
        src/headers/PhysicsSystem.h
        src/headers/PhysicsComponent.h
        src/headers/Circle.h
        src/Shapes/Circle.cpp
        src/CollisionSystem.cpp
        src/headers/CollisionSystem.h
        src/headers/CircleColliderComponent.h
        src/headers/CollisionEvent.h)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/entt
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCE_PATH="${CMAKE_SOURCE_DIR}/Resources/")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm glfw)