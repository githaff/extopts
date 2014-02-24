set(EXAMPLE_DIR "${SRC_DIR}/example")

set(SOURCES
  extopts.c
  extmods.c
  usage.c)
set(HEADERS
  common.h)

include_directories(${INCLUDE_DIR})

add_library(${PROJECT} SHARED
  ${SOURCES} ${HEADERS} ${HEADERS_EXTERN})
set_target_properties (${PROJECT}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})

### Example build
#TODO: exclude from 'all' target
add_subdirectory(${EXAMPLE_DIR})
