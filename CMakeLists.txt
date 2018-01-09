# Setting
#set(ENABLE_BUILD_TESTS true)

# base configuration
cmake_minimum_required(VERSION 3.0)

# Package manager
#include("cmake/Modules/HunterGate.cmake")
#HunterGate(
#        URL "https://github.com/ruslo/hunter/archive/v0.19.216.tar.gz"
#        SHA1 "247d3ca881e9c83e6ac419d55cd08d1775ea077a"
#)

project(inifileparser)

set(CMAKE_CXX_STANDARD 14)

# Enable flag for dev
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -DDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

#set(ENABLE_BUILD_TESTS true)
# cmake -DCMAKE_INSTALL_PREFIX=/usr . && make all install

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

# Include directory
set(INIFILEPARSER_INCLUDE ${CMAKE_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR} ${B2GE_INCLUDE_DIR} ${INIFILEPARSER_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

# Source files
set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDE_FILES})
#set(SOURCE_FILES ${SOURCE_FILES})

# Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})