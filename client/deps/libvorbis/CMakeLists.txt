ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/libvorbis/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/libogg/include)

FILE(GLOB OGG_HEADERS "include/vorbis/*.h" "src/*.h" "src/modes/*.h" "src/books/*.h")
FILE(GLOB OGG_SOURCES "src/*.c" "src/modes/*.c" "src/books/*.c")

add_library(libvorbis STATIC ${OGG_HEADERS} ${OGG_SOURCES})
target_link_libraries(libvorbis libogg)

# Output
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)