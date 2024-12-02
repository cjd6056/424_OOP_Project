cmake_minimum_required(VERSION 3.20)
project(AERSP_424_Final_Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
add_compile_definitions(_USE_MATH_DEFINES)

# Optionally, specify a toolchain file if cross-compiling (commented out for now)
# set(CMAKE_TOOLCHAIN_FILE "${PROJECT_SOURCE_DIR}/toolchain-arm.cmake")

message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}") # To print something.

# list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/matplotplusplus/install")
# find_package(Matplot++ REQUIRED) 
include(GNUInstallDirs)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Define the executable
add_executable(${CMAKE_PROJECT_NAME} ${all_SRCS})

# Enable debugging symbols for development builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

# Optional: Link system libraries for cross-compilation
# For example, for ARM systems, you may need to link system libraries:
# target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_DL_LIBS} m)

# Cross-compilation specific configurations
if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
    
    # Set any cross-compilation specific options here if needed:
    # e.g., set(CMAKE_FIND_ROOT_PATH ${PROJECT_SOURCE_DIR}/toolchain/root)
endif()

