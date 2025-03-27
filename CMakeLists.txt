cmake_minimum_required(VERSION 3.10)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)

# GLM ekle
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)
add_executable(PhysicsEngine 
src/main.cpp
thirdparty/glad/glad.c
)

target_include_directories(PhysicsEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm-master)

target_link_libraries(PhysicsEngine PRIVATE glm)
target_link_libraries(PhysicsEngine PRIVATE glfw)