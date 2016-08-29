SET(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
cmake_minimum_required( VERSION 2.8 )
project(Assimp)

OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
IF(NOT BUILD_SHARED_LIBS)
  SET(LINK_SEARCH_START_STATIC TRUE)
ENDIF(NOT BUILD_SHARED_LIBS)

# Define here the needed parameters
SET (ASSIMP_VERSION_MAJOR 3)
SET (ASSIMP_VERSION_MINOR 2)
SET (ASSIMP_VERSION_PATCH 0) # subversion revision?
SET (ASSIMP_VERSION ${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH})
SET (ASSIMP_SOVERSION 3)
SET (PROJECT_VERSION "${ASSIMP_VERSION}")

SET(ASSIMP_PACKAGE_VERSION "0" CACHE STRING "the package-specific version used for uploading the sources")

# Needed for openddl_parser config, no use of c++11 at this moment
add_definitions( -DOPENDDL_NO_USE_CPP11 )
set_property( GLOBAL PROPERTY CXX_STANDARD 11 )

# Get the current working branch
EXECUTE_PROCESS(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

# Get the latest abbreviated commit hash of the working branch
EXECUTE_PROCESS(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

IF(NOT GIT_COMMIT_HASH)
  SET(GIT_COMMIT_HASH 0)
ENDIF(NOT GIT_COMMIT_HASH)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/revision.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/revision.h
)

include_directories(
    ./
    ${CMAKE_CURRENT_BINARY_DIR}
)

SET(CMAKE_MODULE_PATH       "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )
SET(LIBASSIMP_COMPONENT     "libassimp${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH}" )
SET(LIBASSIMP-DEV_COMPONENT "libassimp${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH}-dev" )
SET(CPACK_COMPONENTS_ALL assimp-bin ${LIBASSIMP_COMPONENT} ${LIBASSIMP-DEV_COMPONENT} assimp-dev)
SET(ASSIMP_LIBRARY_SUFFIX "" CACHE STRING "Suffix to append to library names")

# Workaround to be able to deal with compiler bug "Too many sections" with mingw.
IF( CMAKE_COMPILER_IS_MINGW )
  ADD_DEFINITIONS(-DASSIMP_BUILD_NO_IFC_IMPORTER )
ENDIF()

IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
  IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8) # -fPIC is only required for shared libs on 64 bit
     SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  ENDIF()
  # hide all not-exported symbols
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -std=c++0x" )
ELSEIF(MSVC)
  # enable multi-core compilation with MSVC
  add_compile_options(/MP)
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -Wno-long-long -pedantic -std=c++11" )
ELSEIF( CMAKE_COMPILER_IS_MINGW )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -Wno-long-long -pedantic -std=c++11" )
ENDIF()

INCLUDE (FindPkgConfig)
INCLUDE_DIRECTORIES( include )

INCLUDE (PrecompiledHeader)

# If this is an in-source build (CMAKE_SOURCE_DIR == CMAKE_BINARY_DIR),
# write the library/executable files to the respective directories in the
# source tree. During an out-of-source build, however, do not litter this
# directory, since that is probably what the user wanted to avoid.
IF ( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib" )
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib" )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin" )
ENDIF ( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )

# Cache these to allow the user to override them manually.
SET( ASSIMP_LIB_INSTALL_DIR "lib" CACHE PATH
  "Path the built library files are installed to." )
SET( ASSIMP_INCLUDE_INSTALL_DIR "include" CACHE PATH
  "Path the header files are installed to." )
SET( ASSIMP_BIN_INSTALL_DIR "bin" CACHE PATH
  "Path the tool executables are installed to." )

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
  SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Debug Postfix for lib, samples and tools")
ELSE()
  SET(CMAKE_DEBUG_POSTFIX "" CACHE STRING "Debug Postfix for lib, samples and tools")
ENDIF()

# Only generate this target if no higher-level project already has
IF (NOT TARGET uninstall)
  # add make uninstall capability
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
  add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
ENDIF()

# cmake configuration files
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/assimp-config.cmake.in"         "${CMAKE_CURRENT_BINARY_DIR}/assimp-config.cmake" @ONLY IMMEDIATE)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/assimp-config-version.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/assimp-config-version.cmake" @ONLY IMMEDIATE)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/assimp-config.cmake"             "${CMAKE_CURRENT_BINARY_DIR}/assimp-config-version.cmake" DESTINATION "${ASSIMP_LIB_INSTALL_DIR}/cmake/assimp-${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}" COMPONENT ${LIBASSIMP-DEV_COMPONENT})

FIND_PACKAGE( DirectX )

OPTION ( ASSIMP_NO_EXPORT
  "Disable Assimp's export functionality."
  OFF
)

IF( CMAKE_COMPILER_IS_GNUCXX )
  SET(LIBSTDC++_LIBRARIES -lstdc++)
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

# Search for external dependencies, and build them from source if not found
# Search for zlib
find_package(ZLIB)
IF( NOT ZLIB_FOUND )
  message(STATUS "compiling zlib from souces")
  include(CheckIncludeFile)
  include(CheckTypeSize)
  include(CheckFunctionExists)
  # compile from sources
  add_subdirectory(contrib/zlib)
  SET(ZLIB_FOUND 1)
  SET(ZLIB_LIBRARIES zlibstatic)
  SET(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib/zlib ${CMAKE_CURRENT_BINARY_DIR}/contrib/zlib)
else(NOT ZLIB_FOUND)
  ADD_DEFINITIONS(-DASSIMP_BUILD_NO_OWN_ZLIB)
  SET(ZLIB_LIBRARIES_LINKED -lz)
ENDIF(NOT ZLIB_FOUND)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

# Search for unzip
IF (PKG_CONFIG_FOUND)
  PKG_CHECK_MODULES(UNZIP minizip)
ENDIF (PKG_CONFIG_FOUND)

IF ( ASSIMP_NO_EXPORT )
  ADD_DEFINITIONS( -DASSIMP_BUILD_NO_EXPORT)
  MESSAGE( STATUS "Build an import-only version of Assimp." )
ENDIF( ASSIMP_NO_EXPORT )

SET ( ASSIMP_BUILD_ARCHITECTURE "" CACHE STRING
  "describe the current architecture."
)
IF    ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
ELSE  ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_ARCHITECTURE="${ASSIMP_BUILD_ARCHITECTURE}"' )
ENDIF ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")

# ${CMAKE_GENERATOR}
SET ( ASSIMP_BUILD_COMPILER "" CACHE STRING
  "describe the current compiler."
)
IF    ( ASSIMP_BUILD_COMPILER STREQUAL "")
ELSE  ( ASSIMP_BUILD_COMPILER STREQUAL "")
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_COMPILER="${ASSIMP_BUILD_COMPILER}"' )
ENDIF ( ASSIMP_BUILD_COMPILER STREQUAL "")

MARK_AS_ADVANCED ( ASSIMP_BUILD_ARCHITECTURE ASSIMP_BUILD_COMPILER )


SET ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER OFF CACHE BOOL
  "Build the C4D importer, which relies on the non-free Melange SDK."
)

IF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  IF ( MSVC )
    SET(C4D_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/contrib/Melange/_melange/includes")

    # pick the correct prebuilt library
    IF(MSVC11)
      SET(C4D_LIB_POSTFIX "_2012md")
    ELSEIF(MSVC10)
      SET(C4D_LIB_POSTFIX "_2010md")
    ELSEIF(MSVC90)
      SET(C4D_LIB_POSTFIX "_2008md")
    ELSE()
      MESSAGE( FATAL_ERROR
        "C4D is currently only supported with MSVC 9, 10, 11"
      )
    ENDIF()

    IF(CMAKE_CL_64)
      SET(C4D_LIB_ARCH_POSTFIX "_x64")
    ELSE()
      SET(C4D_LIB_ARCH_POSTFIX "")
    ENDIF()

    SET(C4D_LIB_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/contrib/Melange/_melange/lib/WIN")

    SET(C4D_DEBUG_LIBRARY "${C4D_LIB_BASE_PATH}/debug/_melange_lib${C4D_LIB_ARCH_POSTFIX}${C4D_LIB_POSTFIX}.lib")
    SET(C4D_RELEASE_LIBRARY "${C4D_LIB_BASE_PATH}/release/_melange_lib${C4D_LIB_ARCH_POSTFIX}${C4D_LIB_POSTFIX}.lib")

    # winsock and winmm are necessary dependencies of melange (this is undocumented, but true.)
    SET(C4D_EXTRA_LIBRARIES WSock32.lib Winmm.lib)
  ELSE ()
    MESSAGE( FATAL_ERROR
      "C4D is currently only available on Windows with melange SDK installed in contrib/Melange"
    )
  ENDIF ( MSVC )
ELSE (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  ADD_DEFINITIONS( -DASSIMP_BUILD_NO_C4D_IMPORTER )
ENDIF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)


ADD_SUBDIRECTORY( code/ )
option ( ASSIMP_BUILD_ASSIMP_TOOLS
  "If the supplementary tools for Assimp are built in addition to the library."
  OFF
)
IF ( ASSIMP_BUILD_ASSIMP_TOOLS )
  IF ( WIN32 )
    option ( ASSIMP_BUILD_ASSIMP_VIEW "If the Assimp view tool is built. (requires DirectX)" ${DirectX_FOUND} )
    IF ( ASSIMP_BUILD_ASSIMP_VIEW )
      ADD_SUBDIRECTORY( tools/assimp_view/ )
    ENDIF ( ASSIMP_BUILD_ASSIMP_VIEW )
  ENDIF ( WIN32 )
  
  ADD_SUBDIRECTORY( tools/assimp_cmd/ )
ENDIF ( ASSIMP_BUILD_ASSIMP_TOOLS )

option ( ASSIMP_BUILD_SAMPLES
  "If the official samples are built as well (needs Glut)."
  OFF
)

IF ( ASSIMP_BUILD_SAMPLES)
  IF ( WIN32 )
    ADD_SUBDIRECTORY( samples/SimpleTexturedOpenGL/ )
  ENDIF ( WIN32 )
  ADD_SUBDIRECTORY( samples/SimpleOpenGL/ )
ENDIF ( ASSIMP_BUILD_SAMPLES )

OPTION ( ASSIMP_BUILD_TESTS
  "If the test suite for Assimp is built in addition to the library."
  OFF
)

IF ( ASSIMP_BUILD_TESTS )
  ADD_SUBDIRECTORY( test/ )
ENDIF ( ASSIMP_BUILD_TESTS )

IF(MSVC)
  OPTION ( ASSIMP_INSTALL_PDB
    "Install MSVC debug files."
    ON
  )
ENDIF(MSVC)

# Generate a pkg-config .pc for the Assimp library.
CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/assimp.pc.in" "${PROJECT_BINARY_DIR}/assimp.pc" @ONLY )