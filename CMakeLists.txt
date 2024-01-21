cmake_minimum_required(VERSION 3.0.0)
project(Guitar VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glad)

include_directories(
  vendor/glfw/include
  vendor/glm
  vendor/imgui
  vendor/glad/include
  include/
)

add_executable(
  Guitar 
  src/main.cpp
  src/app/Window.cpp
  src/core/GLBuffer.cpp
  src/core/GLShader.cpp
  src/core/GLFramebuffer.cpp
)

target_link_libraries(Guitar glfw glm imgui glad)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
