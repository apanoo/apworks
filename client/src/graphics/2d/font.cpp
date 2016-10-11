#include "font.h"

nario::Font::~Font()
{

}

void nario::Font::setScale(float x, float y)
{
	_scale = Vector2(x, y);
}

nario::Font::Font(std::string name, std::string filename, unsigned int size)
	:_name(name), _filename(filename), _size(size)
{
	_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
	_FTFont = ftgl::texture_font_new_from_file(_FTAtlas, (float)_size, _filename.c_str());
}

