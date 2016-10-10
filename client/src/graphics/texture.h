#pragma once
#include <string>
#include "utils/stdafx.h"
#include <FreeImage.h>

namespace nario {
	class Texture
	{
	public:
		Texture(const std::string& filename);
		~Texture();

		void bind() const;
		void unbind() const;

		inline unsigned int getWidth() const { return _width; }
		inline unsigned int getHeight() const { return _height; }
		inline GLuint getId() const { return _tid; }
	private:
		GLuint load();
	private:
		std::string _filename;
		GLuint _tid;
		GLsizei _width, _height;
	};
}