# Projects Settings
cmake_minimum_required (VERSION 3.12)
project (OpenGLSandbox)

# Define the include DIRs
include_directories(
    "${CMAKE_SOURCE_DIR}/dependencies/include"
    "${CMAKE_SOURCE_DIR}/common"
)

# Add .lib files
link_directories("${CMAKE_SOURCE_DIR}/dependencies/lib")

# The main executable
add_executable(${PROJECT_NAME}
  src/main.cpp
  common/Application.h 
  common/Application.cpp
  src/MCApplication.h
  src/MCApplication.cpp
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenGL REQUIRED)


set(LIBS glfw3 glew32 OpenGL::GL)
# Define the link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})