set (EXAMPLE_DIR "${SRC_DIR}/example")

set (SOURCES
  extopts.c
  extmods.c
  usage.c)
set (HEADERS
  common.h)

include_directories (${INCLUDE_DIR})

add_library (${PROJECT} SHARED
  ${SOURCES} ${HEADERS} ${HEADERS_EXTERN})
set_target_properties (${PROJECT}
  PROPERTIES
  VERSION "${EXTOPTS_VERSION}" SOVERSION "${EXTOPTS_VERSION_MAJOR}"
  LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})

### Example build
add_subdirectory (${EXAMPLE_DIR} EXCLUDE_FROM_ALL)

### Install rules
install (TARGETS ${PROJECT} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install (FILES ${HEADERS_EXTERN} DESTINATION "include/${PROJECT}")
