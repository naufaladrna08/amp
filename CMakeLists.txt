cmake_minimum_required(VERSION 3.0.0)
project(Guitar VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/assimp)

include_directories(
  vendor/glfw/include
  vendor/glm
  vendor/imgui
  vendor/glad/include
  vendor/assimp/include
  vendor/stb
  include/
)

add_executable(
  Guitar 
  src/main.cpp
  src/app/Window.cpp
  src/core/GLBuffer.cpp
  src/core/GLShader.cpp
  src/core/GLFramebuffer.cpp
  src/engine/Mesh.cpp
  src/engine/Model.cpp
  src/engine/StbImage.cpp
  src/ui/FileDialog.cpp
)

target_link_libraries(Guitar glfw glm imgui glad assimp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
