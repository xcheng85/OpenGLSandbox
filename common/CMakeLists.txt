# Projects Settings
cmake_minimum_required (VERSION 3.12)
project (common)
message("configuring library: " ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Define the include DIRs
include_directories(
    "${PROJECT_ROOT}/dependencies/include"
    "${PROJECT_ROOT}/common"
    "${PROJECT_ROOT}"
)

message("project root: " ${PROJECT_ROOT})

# Add .lib files
link_directories("${PROJECT_ROOT}/dependencies/lib")

# The main executable
add_library(${PROJECT_NAME}
  Model.h
  Model.cpp 
  Texture.h 
  Texture.cpp
  Application.h
  Application.cpp
  Common.h 
  CommonGL.h 
  Renderer.h 
  RendererGL.h 
  RendererGL.cpp 
  VertexInputAttributeGL.h 
  VertexInputAttributeGL.cpp 
  BufferGL.h
  BufferGL.cpp
  VertexInputBindingGL.h 
  VertexInputBindingGL.cpp
  PipelineVertexInputStateGL.h
  PipelineVertexInputStateGL.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

find_package(OpenGL REQUIRED)
set(LIBS glfw3 glew32 assimp OpenGL::GL glWrapper)
# Define the link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})