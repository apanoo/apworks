#include <iostream>
#include <gl/glew.h>

// nario lib
#include "../nario.h"

int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 800, 600);

	while (!window.closed())
	{
		std::cout << "loop" << std::endl;
		window.clear();
		//glBegin(GL_TRIANGLES);

		//glEnd();
		window.update();
	}

    return 0;
}