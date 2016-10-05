set (MODULE_NAME libwebp)

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-D_LIB)
endif(NOT BUILD_SHARED_LIBS)

file (GLOB ${MODULE_NAME}_SRCS src/dec/*.c src/demux/*.c src/dsp/*.c src/enc/*.c src/mux/*.c src/utils/*.c)

add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)