set (MODULE_NAME libjxr)

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-D_LIB -DDISABLE_PERF_MEASUREMENT)
endif(NOT BUILD_SHARED_LIBS)

include_directories( image/sys jxrgluelib )

file (GLOB ${MODULE_NAME}_SRCS image/decode/*.c image/encode/*.c image/sys/*.c jxrgluelib/*.c)

add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)