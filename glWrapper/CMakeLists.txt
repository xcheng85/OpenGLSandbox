# Projects Settings
cmake_minimum_required (VERSION 3.12)
project (glWrapper)
message("configuring library: " ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Define the include DIRs
include_directories(
    "${PROJECT_ROOT}/dependencies/include"
    "${PROJECT_ROOT}"
)

message("project root: " ${PROJECT_ROOT})

# Add .lib files
link_directories("${PROJECT_ROOT}/dependencies/lib")

# The main executable
add_library(${PROJECT_NAME}
  ObjectGL.h
  ObjectGL.cpp 
  BufferGL.h
  BufferGL.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

find_package(OpenGL REQUIRED)
set(LIBS glew32)
# Define the link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})