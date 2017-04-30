set (EXAMPLE_DIR "${SRC_DIR}/example")

set (SOURCES
  extopts.c
  extmods.c
  usage.c)
set (HEADERS
  common.h)

include_directories (${INCLUDE_DIR})

add_library (${LIB_STAT} STATIC
  ${SOURCES} ${HEADERS} ${HEADERS_EXTERN})
set_target_properties (${LIB_STAT}
  PROPERTIES
  OUTPUT_NAME ${PROJECT}
  VERSION "${EXTOPTS_VERSION}" SOVERSION "${EXTOPTS_VERSION_MAJOR}")
install (TARGETS ${LIB_STAT}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

if (NOT ${DISABLE_SHARED})
  add_library (${LIB_DYN} SHARED
    ${SOURCES} ${HEADERS} ${HEADERS_EXTERN})
  set_target_properties (${LIB_DYN}
    PROPERTIES
    OUTPUT_NAME ${PROJECT}
    VERSION "${EXTOPTS_VERSION}" SOVERSION "${EXTOPTS_VERSION_MAJOR}")
  install (TARGETS ${LIB_DYN}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif ()

### Example build
add_subdirectory (${EXAMPLE_DIR} EXCLUDE_FROM_ALL)

