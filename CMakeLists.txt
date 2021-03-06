cmake_minimum_required (VERSION 2.8)

if (NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

option (DISABLE_SHARED "Disable shared library build" OFF)

### Name of whole complex
set (PROJECT "extopts")
if (NOT ${DISABLE_SHARED})
  set (LIB_DYN "dynamic")
endif ()
set (LIB_STAT "static")
project (${PROJECT})

# Set compile parameters
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
# Set additional warnings
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

### Project directories
## CMake modules
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
## Sources
set (SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set (INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

## Installation paths if not specified
if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set (CMAKE_INSTALL_LIBDIR "lib")
endif (NOT DEFINED CMAKE_INSTALL_LIBDIR)
if (NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
  set (CMAKE_INSTALL_INCLUDEDIR "include")
endif (NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
set (CMAKE_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/${PROJECT}")
## Paths for *-config.cmake file
set (EXTOPTS_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set (EXTOPTS_LIB_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

### Public extopts library interface
set (HEADERS_EXTERN
  ${INCLUDE_DIR}/${PROJECT}/extopts.h
  ${INCLUDE_DIR}/${PROJECT}/extmods.h)

### Extract version numbers
include (git-version)
git_version_extract (EXTOPTS)

add_subdirectory (${SRC_DIR})

### Pkg-config generation
set(prefix ${CMAKE_INSTALL_PREFIX})
configure_file(extopts.pc.in extopts.pc @ONLY)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/extopts.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

### CMake find module generation
configure_file(extopts-config.cmake.in extopts-config.cmake @ONLY)
configure_file(extopts-config-version.cmake.in extopts-config-version.cmake @ONLY)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/extopts-config.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR})
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/extopts-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR})

### Packaging setup
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Extopts library")
set (CPACK_PACKAGE_VENDOR "haff")
set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${EXTOPTS_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${EXTOPTS_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${EXTOPTS_VERSION_PATCH}")
set (CPACK_SOURCE_GENERATOR "TGZ")
set (CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${EXTOPTS_VERSION_FULL}")
set (CPACK_SOURCE_IGNORE_FILES 
  ".*~"
  "#.*#"
  ".*.tar.gz"
  ".*.pc$"
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
add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

### Install rules
install (FILES ${HEADERS_EXTERN} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT}")
