#include "texture.h"
#include "resources_mgr.h"

nario::TextureWrap nario::Texture::_wrapMode = nario::TextureWrap::REPEAT;
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
	BYTE* pixels = ResourcesMgr::getInstance()->loadImage(_filename.c_str(), &_width, &_height, &_bits);
	if (_bits != 24 && _bits != 32)
	{
		aplog::logerr(_filename, " not surport! bits shuold be 24 or 32. ");
	}
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result); // bind
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)_wrapMode);
	glTexImage2D(GL_TEXTURE_2D, 0, _bits == 32? GL_RGBA:GL_RGB, _width, _height, 0, _bits == 32?GL_BGRA:GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0); // unbind
	
	delete[] pixels;

	return result;
}

nario::Texture::Texture(const std::string& filename)
	: _filename(filename)
{
	_tid = load();
}

