set( _glew_HEADER_SEARCH_DIRS
"${CMAKE_SOURCE_DIR}/dependencies/include")
set( _glew_LIB_SEARCH_DIRS
"${CMAKE_SOURCE_DIR}/dependencies/lib")

# Check environment for root search directory
set( _glew_ENV_ROOT $ENV{GLEW_ROOT} )
if( NOT GLEW_ROOT AND _glew_ENV_ROOT )
	set(GLEW_ROOT ${_glew_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( GLEW_ROOT )
	list( INSERT _glew_HEADER_SEARCH_DIRS 0 "${GLFW3_ROOT}/include" )
	list( INSERT _glew_LIB_SEARCH_DIRS 0 "${GLFW3_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(GLEW_INCLUDE_DIR "/GL/glew.h"
PATHS ${_glew_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(GLEW_LIBRARY NAMES glew32 PATHS ${_glew_LIB_SEARCH_DIRS} )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW DEFAULT_MSG GLEW_LIBRARY GLEW_INCLUDE_DIR)