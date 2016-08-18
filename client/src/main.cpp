#include <iostream>

// OpenGL
#include <GL/glew.h>

#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame mainGame;
	mainGame.run();

	std::cout << "Enter any key to quit" << std::endl;
	int a;
	std::cin >> a;
    return 0;
}