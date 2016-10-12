#include "texture.h"
#include "resources_mgr.h"

nario::Texture::~Texture()
{

}

void nario::Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, _tid);
}

void nario::Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint nario::Texture::load()
{
	BYTE* pixels = ResourcesMgr::getInstance()->loadImage(_filename.c_str(), &_width, &_height);
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result); // bind
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0); // unbind
	
	delete[] pixels;

	return result;
}

nario::Texture::Texture(const std::string& filename)
	: _filename(filename)
{
	_tid = load();
}

