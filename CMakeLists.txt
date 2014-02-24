cmake_minimum_required(VERSION 2.8)

# Set compile parameters
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O0 -g")
# Set additional warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

### Name of whole complex
set(PROJECT "extopts")
project(${PROJECT})

### Project directories
## Build product directories
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")
## Sources
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

if(NOT EXISTS "${BUILD_DIR}")
  file(MAKE_DIRECTORY "${DOXROOT}")
endif()

### Public extopts library interface
set(HEADERS_EXTERN
  ${INCLUDE_DIR}/${PROJECT}/extopts.h
  ${INCLUDE_DIR}/${PROJECT}/extmods.h)

add_subdirectory(${SRC_DIR})
