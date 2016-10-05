set (MODULE_NAME librawlite)

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-D_LIB -DLIBRAW_NODLL)
endif(NOT BUILD_SHARED_LIBS)

include_directories( . )

file (GLOB ${MODULE_NAME}_SRCS 
	internal/dcraw_common.cpp
	internal/dcraw_fileio.cpp
	internal/demosaic_packs.cpp
	src/*.cpp
	)

add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)