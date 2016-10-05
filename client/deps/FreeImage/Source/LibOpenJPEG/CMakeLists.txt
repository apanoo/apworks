set (MODULE_NAME libopenjpeg)

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-D_LIB -DOPJ_STATIC)
endif(NOT BUILD_SHARED_LIBS)

file (GLOB ${MODULE_NAME}_SRCS 
	bio.c
	cio.c
	dwt.c
	event.c
	function_list.c
	image.c
	invert.c
	j2k.c
	jp2.c
	mct.c
	mqc.c
	openjpeg.c
	opj_clock.c
	pi.c
	raw.c
	t1.c
	t2.c
	tcd.c
tgt.c
)

add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)