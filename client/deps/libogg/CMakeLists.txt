INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/libogg/include)

FILE(GLOB OGG_HEADERS "include/ogg/config_types.h" "include/ogg/ogg.h" "include/ogg/os_types.h")
FILE(GLOB OGG_SOURCES "src/bitwise.c" "src/framing.c")

add_library(libogg STATIC ${OGG_HEADERS} ${OGG_SOURCES})

# Output
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)