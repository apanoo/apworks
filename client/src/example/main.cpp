#include <iostream>
#include <gl/glew.h>

// nario lib
#include "../nario.h"

int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 960, 540);

	GLfloat vertices[] = {
		0,  0, 0,
		8,  0, 0,
		0,  3, 0,
		0,  3, 0,
		8,  3, 0,
		8,  0, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();

	Matrix4 ortho = Matrix4().orthographicMatrix(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Matrix4().translationMatrix(Vector3(4, 3, 0)));
	shader.setUniform2f("light_pos", Vector2(4.0f, 1.5f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

    return 0;
}