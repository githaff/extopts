set (PROJECT_EXAMPLE_DYNAMIC "example_dynamic")
set (PROJECT_EXAMPLE_STATIC "example_static")

set (SOURCES_EXAMPLE
  main.c
  modules.c)

configure_file ("config.h.in" "config.h")

include_directories (${INCLUDE_DIR})
add_executable (${PROJECT_EXAMPLE_DYNAMIC}
  ${SOURCES_EXAMPLE}
  ${HEADERS_EXTERN})
add_dependencies(${PROJECT_EXAMPLE_DYNAMIC} ${LIB_DYN})
set_target_properties (${PROJECT_EXAMPLE_DYNAMIC}
  PROPERTIES
  OUTPUT_NAME "example"
  RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
target_link_libraries (${PROJECT_EXAMPLE_DYNAMIC} ${BUILD_DIR}/libextopts.so)

add_executable (${PROJECT_EXAMPLE_STATIC}
  ${SOURCES_EXAMPLE}
  ${HEADERS_EXTERN})
add_dependencies(${PROJECT_EXAMPLE_STATIC} ${LIB_STAT})
set_target_properties (${PROJECT_EXAMPLE_STATIC}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
target_link_libraries (${PROJECT_EXAMPLE_STATIC} ${BUILD_DIR}/libextopts.a)

add_custom_target (example
  DEPENDS ${PROJECT_EXAMPLE_STATIC} ${PROJECT_EXAMPLE_DYNAMIC})
