# Minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# Project name
project(SDL_OpenGL_Project)

# C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
add_compile_options(-Wall -m64)

# Detect OS and set platform-specific settings
if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:/SDL2/lib/cmake/SDL2")
    find_package(SDL2 REQUIRED CONFIG)
    include_directories(C:/SDL2/include)
    link_directories(C:/SDL2/lib)
    link_directories(C:/OpenGLGLEW/lib/Release/x64)
    set(LIBRARIES mingw32 SDL2main SDL2 SDL2_image glew32 glew32s opengl32)
elseif(UNIX AND NOT APPLE)
        find_package(SDL2 REQUIRED)
        find_package(GLEW REQUIRED) # Find GLEW on Linux
        # Link to OpenGL library
        find_package(OpenGL REQUIRED)
        
        set(LIBRARIES SDL2 SDL2_image ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
endif()
# Global include directories
include_directories(include)

# Source files
file(GLOB SOURCES src/*.cpp)

# Debug configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Release configuration
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Set the output directory for the executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# Executable for debug
add_executable(SDLPlatformer_debug ${SOURCES})
target_link_libraries(SDLPlatformer_debug ${LIBRARIES})
set_target_properties(SDLPlatformer_debug PROPERTIES
                      OUTPUT_NAME SDLPlatformer_debug
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)

# Executable for release
add_executable(SDLPlatformer_release ${SOURCES})
target_link_libraries(SDLPlatformer_release ${LIBRARIES})
set_target_properties(SDLPlatformer_release PROPERTIES
                      OUTPUT_NAME SDLPlatformer_release
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/release)
