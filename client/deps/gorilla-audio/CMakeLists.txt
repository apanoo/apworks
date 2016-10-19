ADD_DEFINITIONS(-D_WINDLL)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/openal/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/libvorbis/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/libogg/include)

FILE(GLOB GORILLA_HEADERS "src/common/gc_common.h" "src/common/gc_thread.h" "src/common/gc_types.h" "src/gau.h" "src/ga_internal.h" "src/devices/ga_openal.h" "src/ga.h" )
FILE(GLOB GORILLA_SOURCES "src/common/gc_common.c" "src/common/gc_thread.c" "src/devices/ga_openal.c" "src/ga.c" "src/gau.c" "src/ga_stream.c")

add_library(gorilla SHARED ${GORILLA_HEADERS} ${GORILLA_SOURCES})
target_link_libraries(gorilla libvorbis libogg openal)

# Output
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

SET_TARGET_PROPERTIES(gorilla PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)