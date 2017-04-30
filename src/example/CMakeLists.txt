set (PROJECT_EXAMPLE "example")

set (SOURCES_EXAMPLE
  main.c
  modules.c)

configure_file ("config.h.in" "config.h")

include_directories (
  ${INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})

add_executable (${PROJECT_EXAMPLE}
  ${SOURCES_EXAMPLE}
  ${HEADERS_EXTERN})
add_dependencies(${PROJECT_EXAMPLE} ${LIB_STAT})
set_target_properties (${PROJECT_EXAMPLE}
  PROPERTIES
  OUTPUT_NAME "example")
target_link_libraries (${PROJECT_EXAMPLE} ${LIB_STAT})
