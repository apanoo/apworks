set (MODULE_NAME zlib)

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-D_LIB)
endif(NOT BUILD_SHARED_LIBS)

file (GLOB ${MODULE_NAME}_SRCS *.c)

add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

