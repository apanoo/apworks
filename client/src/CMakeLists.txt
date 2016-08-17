# All sources in src folder
AUX_SOURCE_DIRECTORY (. EXE_SRC) 

# Target name
SET(
    OUT_PUT_TARGET
    "Apclient"
)

# Common include 
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps)

# Common library
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

# SDL2
SET( SDL_STATIC OFF CACHE BOOL "Build the static SDL library" )
SET( SDL_SHARED ON CACHE BOOL "Build the shared SDL library" )
ADD_DEFINITIONS( -DSDL_MAIN_HANDLED )   # Important : no sdl-main compile
SET( EXTRA_LIBS ${EXTRA_LIBS} SDL2 )
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/SDL2/include)

# GLEW
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DGLEW_NO_GLU)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/glew2.0)
SET (EXTRA_LIBS ${EXTRA_LIBS} glew)

# Box2D
OPTION(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
IF(BOX2D_BUILD_STATIC)
    MESSAGE(STATUS "Build Box2D static libraries")
    SET (EXTRA_LIBS ${EXTRA_LIBS} Box2D)
ENDIF(BOX2D_BUILD_STATIC)

# Executable
ADD_EXECUTABLE(
    ${OUT_PUT_TARGET} ${EXE_SRC}
)

# Link libs
TARGET_LINK_LIBRARIES(
    ${OUT_PUT_TARGET} ${EXTRA_LIBS}
)

# Executable output path
SET(
    EXECUTABLE_OUTPUT_PATH
    ${PROJECT_SOURCE_DIR}/bin
)