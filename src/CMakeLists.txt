
cmake_minimum_required(VERSION 3.5)
project(BeeSafe)

# For Clangd langage server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Packages 
find_package(OpenGL REQUIRED)

# Check 
if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (Seperate Build and Source direcotries)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
  message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Building the Dependecies
add_subdirectory(dependencies)

include_directories(
  dependencies/glm/
  dependencies/glfw-3.3.8/include/GLFW/
  dependencies/glew-2.2.0/include/
  )

# Create variable ALL_LIBS that contains the Libaries
# glfw is  defined in its CMakeLists.txt
# GLEW_220 is defined by us in the dependencies/CMakeLists.txt
# OPENGL_LIBARY is a System Variable i guess
set(ALL_LIBS
  ${OPENGL_LIBRARY}
  GLEW_220
  glfw
)

# Add Executeable Here:

add_executable(BeeSafe
  main.cpp
  Window.hpp
  Window.cpp
  game_object.hpp
  game.hpp
  game.cpp
  bee.hpp
  bee.cpp
  wasp.hpp
  wasp.cpp
  menu.hpp
  menu.cpp
  flower.hpp
  flower.cpp
  texture.hpp
  texture.cpp
  common/shader.cpp
  common/shader.hpp
  common/stb_image.h
  common/stb_image.cpp
  shader/SimpleFragmentshader.fragmentshader
  shader/SimpleVertexshader.vertexshader
)

target_link_libraries(BeeSafe
  ${ALL_LIBS}
)


# To Copy the Executeable in the source directory
# This is nessecary if we have Shaders, that we Include
		 
add_custom_command(TARGET BeeSafe 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "BeeSafe${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_SOURCE_DIR}/")
