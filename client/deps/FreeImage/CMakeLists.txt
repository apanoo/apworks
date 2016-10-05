project(FreeImage)
cmake_minimum_required(VERSION 2.8)

# Static by default.
set (BUILD_SHARED_LIBS OFF)

if (NOT BUILD_SHARED_LIBS)
	set (PNG_STATIC ON)
	set (PNG_SHARED OFF)
endif (NOT BUILD_SHARED_LIBS)

add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)

add_subdirectory (Source/FreeImage)

option (USE_EXTERNAL_LIBPNG ON)
option (USE_EXTERNAL_OPENJPEG ON)

if (NOT ${USE_EXTERNAL_LIBPNG})
	add_subdirectory (Source/LibPNG)
else()
	include_directories(${PNG_INCLUDE_DIRECTORIES})
endif()


if (NOT ${USE_EXTERNAL_OPENJPEG})
	add_subdirectory (Source/LibOpenJPEG)
else()
	include_directories(${OPENJPEG_INCLUDE_DIRECTORIES})
endif()

add_subdirectory (Source/LibJPEG)
add_subdirectory (Source/LibJXR)
add_subdirectory (Source/LibRawLite)
add_subdirectory (Source/LibTIFF4)
add_subdirectory (Source/LibWebP)
add_subdirectory (Source/OpenEXR)
# add_subdirectory (Source/ZLib)

install (FILES Source/FreeImage.h DESTINATION include)