#include <iostream>
#include <gl/glew.h>

// nario lib
#include "../nario.h"

int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 960, 540);
#if 0
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
#endif

	GLfloat vertices[] = {
		0,  0, 0,
		0,  3, 0,
		8,  3, 0,
		8,  0, 0
	};

	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colorsA[] = {
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1
	};

	GLfloat colorsB[] = {
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1
	};

	VertexArray sprite1, sprite2;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

	sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);

	Matrix4 ortho = Matrix4().orthographicMatrix(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);
	
	shader.setUniform2f("light_pos", Vector2(0.0f, 0.0f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		int x = window.getMouseX();
		int y = window.getMouseY(); 
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", Matrix4().translationMatrix(Vector3(4, 5, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", Matrix4().translationMatrix(Vector3(4, 1.5, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();

		window.update();
	}

    return 0;
}