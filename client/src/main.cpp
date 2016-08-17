// glew only
#define GLEW_NO_GLU

// windows header file
#if _WIN32 
    #include <windows.h>
#endif

#include <stdio.h>

// SDL
#include <SDL.h>

// OpenGL
#include <GL/glew.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
	printf("hello\n");
	getchar();
    return 0;
}