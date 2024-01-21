project(glad)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(
  glad STATIC 
  src/glad.c
)