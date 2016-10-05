set (MODULE_NAME freeimage)

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-DFREEIMAGE_LIB -DLIBRAW_NODLL -DOPJ_STATIC)
endif(NOT BUILD_SHARED_LIBS)

include_directories (.. ../ZLib ../DeprecationManager ../OpenEXR ../OpenEXR/Half ../OpenEXR/Iex ../OpenEXR/IlmImf ../OpenEXR/Imath ../OpenEXR/IlmThread ../LibJXR/jxrgluelib ../LibJXR/image/sys)

file (GLOB ${MODULE_NAME}_SRCS *.cpp ../DeprecationManager/*.cpp ../FreeImageToolkit/*.cpp ../Metadata/*.cpp )

add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

# output dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)