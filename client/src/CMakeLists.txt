# all sources in src folder
aux_source_directory (. EXE_SRC)

# target name
set(
    OUT_PUT_TARGET
    "Apclient"
)

# SDL2
include_directories(
    ${PROJECT_SOURCE_DIR}/deps/SDL2-2.0.4/include
)
link_directories(
    ${PROJECT_SOURCE_DIR}/deps/SDL2-2.0.4/lib
)

# GLEW
include_directories(
    ${PROJECT_SOURCE_DIR}/deps/glew2.0/include
)
link_directories(
    ${PROJECT_SOURCE_DIR}/deps/glew2.0/lib
)

# executable project
add_executable(
    ${OUT_PUT_TARGET} ${EXE_SRC}
)

# link libs
if(WIN32)
    target_link_libraries(
        ${OUT_PUT_TARGET} SDL2 SDL2main SDL2_test glew32
    )
else(WIN32)
    target_link_libraries(
        ${OUT_PUT_TARGET} SDL2 SDL2main SDL2_test GLEW
    )
endif(WIN32)


# out put path
set(
    EXECUTABLE_OUTPUT_PATH
    ${PROJECT_SOURCE_DIR}/bin
)