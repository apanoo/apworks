# Cmake version
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Solution name
SET( SOLUTION_NAME "Client" )

# Create solution
PROJECT( ${SOLUTION_NAME} )

# 项目分类
set_property(GLOBAL PROPERTY USE_FOLDERS On)

# Check and suport c++ 11
INCLUDE( CheckCXXCompilerFlag )  
CHECK_CXX_COMPILER_FLAG( "-std=c++11" COMPILER_SUPPORTS_CXX11 )  
CHECK_CXX_COMPILER_FLAG( "-std=c++0x" COMPILER_SUPPORTS_CXX0X )  
IF( COMPILER_SUPPORTS_CXX11 )  
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )  
ELSEIF( COMPILER_SUPPORTS_CXX0X )  
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )  
ELSE()  
     MESSAGE( FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler." )  
ENDIF()  

# compile srouce
ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( deps/Box2D )
ADD_SUBDIRECTORY( deps/glew2.0/GL )
ADD_SUBDIRECTORY( deps/SDL2 )
ADD_SUBDIRECTORY( deps/assimp )
ADD_SUBDIRECTORY( deps/FreeImage )
ADD_SUBDIRECTORY( deps/freetype )
ADD_SUBDIRECTORY( deps/openal )

set_target_properties(uninstall PROPERTIES FOLDER "CMakePredefinedTargets") 

set_target_properties(assimp PROPERTIES FOLDER "Dependencies") 
set_target_properties(Box2D PROPERTIES FOLDER "Dependencies") 
set_target_properties(glew PROPERTIES FOLDER "Dependencies") 
set_target_properties(SDL2 PROPERTIES FOLDER "Dependencies") 
set_target_properties(freetype PROPERTIES FOLDER "Dependencies")

set_target_properties(freeimage PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libjpeg PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libjxr PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libopenexr PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libopenjpeg PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libpng PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(librawlite PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libtiff4 PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(libwebp PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(zlib PROPERTIES FOLDER "Dependencies/freeimage") 
set_target_properties(openal PROPERTIES FOLDER "Dependencies/openal") 
set_target_properties(common PROPERTIES FOLDER "Dependencies/openal") 
