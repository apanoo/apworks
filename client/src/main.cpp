
// windows header file
#if _WIN32 
    #include <windows.h>
#endif

#include <stdio.h>

// OpenGL
#include <GL/glew.h>
// SDL
#include <SDL.h>


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	printf("hello\n");
	getchar();
    return 0;
}