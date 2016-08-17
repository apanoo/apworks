# glew

include_directories(../)
add_definitions( -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS -DGLEW_NO_GLU)

add_library(glew STATIC 
	glew.c
	glew.h
	glxew.h
	wglew.h
)

# Output
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
