#pragma once
#include <string>
#include "log/aplog.h"
#include "utils/stdafx.h"
#include <FreeImage.h>

namespace nario {
	enum TextureWrap
	{
		REPEAT			= GL_REPEAT,
		CLAMP			= GL_CLAMP,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE   = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};
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

		// texture wrap mode
		inline static void setWrap(TextureWrap mode) { _wrapMode = mode; }
	private:
		GLuint load();
	private:
		std::string _filename;
		GLuint _tid;
		GLsizei _width, _height;
		GLsizei _bits;

		static TextureWrap _wrapMode;
	};
}