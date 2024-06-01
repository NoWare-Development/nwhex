set(PROJECT_NAME nwhex)

project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 99)

set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/args.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/help.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/hex.c"
  )

add_executable(${PROJECT_NAME} ${SOURCES})
