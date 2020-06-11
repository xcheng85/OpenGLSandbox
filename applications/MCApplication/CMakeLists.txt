# Projects Settings
cmake_minimum_required (VERSION 3.12)
project (MCApplication)

# Define the include DIRs
include_directories(
    "${PROJECT_ROOT}/dependencies/include"
    "${PROJECT_ROOT}/common"
)

# Add .lib files
link_directories("${PROJECT_ROOT}/dependencies/lib")

# The main executable
add_executable(${PROJECT_NAME}
  main.cpp
  MCApplication.h
  MCApplication.cpp
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

find_package(OpenGL REQUIRED)
set(LIBS glfw3 glew32 assimp OpenGL::GL common )
# Define the link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})