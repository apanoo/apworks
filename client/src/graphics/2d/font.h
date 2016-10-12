#pragma once
#include "extension/freetype-gl/freetype-gl.h"
#include "math/maths.h"
#include <string>

namespace nario {
	class Font
	{
	public:
		Font(std::string name, std::string filename, unsigned int size = 32);
		~Font();

		// set font scale
		void setScale(float x, float y);

		inline ftgl::texture_font_t* getFTFont() const { return _FTFont; }
		inline const std::string& getName() const { return _name; }
		inline const Vector2& getScale() const { return _scale; }
		inline const std::string& getFilename() const { return _filename; }
		inline const unsigned int getSize() const { return _size; }
		inline const unsigned int getId() const { return _FTAtlas->id; }
	private:
		ftgl::texture_atlas_t* _FTAtlas;
		ftgl::texture_font_t* _FTFont;
		unsigned int _size;
		std::string _filename;
		std::string _name;
		Vector2 _scale;
	};
}