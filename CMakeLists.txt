cmake_minimum_required(VERSION 3.10)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)

add_executable(${CMAKE_PROJECT_NAME} 
    src/main.cpp
    thirdparty/glad/glad.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/entt
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCE_PATH="${CMAKE_SOURCE_DIR}/Resources/")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm glfw)