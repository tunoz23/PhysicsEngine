cmake_minimum_required(VERSION 3.10)

project(PhysicsEngine)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    thirdparty/glad/glad.c

        #<----------------headers---------------->#
        src/headers/Systems/RenderSystem.h
        src/headers/Systems/WindowSystem.h
        src/headers/Systems/PhysicsSystem.h
        src/headers/Systems/CollisionSystem.h
        src/headers/Systems/CameraSystem.h

        src/headers/Components/MeshComponent.h
        src/headers/Components/PhysicsComponent.h
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

        #<----------------cpps---------------->#
        src/Scene.cpp

        src/Systems/RenderSystem.cpp
        src/Systems/WindowSystem.cpp
        src/Systems/PhysicsSystem.cpp
        src/Systems/CollisionSystem.cpp
        src/Systems/CameraSystem.cpp

        src/Shapes/Circle.cpp
        src/Shapes/Rectangle.cpp
        src/Shapes/Cube.cpp
        src/Shapes/Sphere.cpp)


target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Components/ColliderComponents
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Systems
    #<----------------thirdparty---------------->#
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/entt
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCE_PATH="${CMAKE_SOURCE_DIR}/Resources/")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm glfw)
