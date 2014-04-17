set(PROJECT_EXAMPLE "example")

set(SOURCES_EXAMPLE
  main.c
  modules.c)

configure_file ("config.h.in" "config.h")

include_directories(${INCLUDE_DIR})

add_executable(${PROJECT_EXAMPLE}
  ${SOURCES_EXAMPLE}
  ${HEADERS_EXTERN})

set_target_properties(${PROJECT_EXAMPLE}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
target_link_libraries(${PROJECT_EXAMPLE} ${PROJECT})

