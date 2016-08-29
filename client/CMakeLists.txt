# Cmake version
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Solution name
SET( SOLUTION_NAME "Client" )

# Create solution
PROJECT( ${SOLUTION_NAME} )

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
ADD_SUBDIRECTORY( src/example )
