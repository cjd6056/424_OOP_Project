cmake_minimum_required(VERSION 3.20)
project(AERSP_424_Final_Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable
add_executable(${PROJECT_NAME} Snake_OOP.cpp)

# Include necessary directories
include_directories(${CMAKE_SOURCE_DIR})

# Link against Windows libraries if necessary
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE user32 kernel32)
endif()

# Enable debugging symbols for development builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()
