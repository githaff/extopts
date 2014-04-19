cmake_minimum_required(VERSION 2.8)

# Set compile parameters
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O0 -g")
# Set additional warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

### Library version
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

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

### Packaging setup
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Extopts library")
set (CPACK_PACKAGE_VENDOR "haff")
set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_SOURCE_GENERATOR "TGZ")
set (CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
set (CPACK_SOURCE_IGNORE_FILES 
  ".*~"
  "#.*#"
  ".*.tar.gz"
  "/.git"
  "/build"
  "/_CPack_Packages"
  ".gitignore"
  "CMakeCache.txt"
  "CMakeFiles"
  "CPackConfig.cmake"
  "CPackSourceConfig.cmake"
  "Makefile"
  "cmake_install.cmake"
  "install_manifest.txt"
)
include (CPack)
## Add alias to default 'dist' target
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
