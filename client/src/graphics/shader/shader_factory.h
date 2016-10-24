#pragma once
#include "shader.h"

namespace nario {
	class ShaderFactory
	{
	public:
		static Shader* defaultShader();
		static Shader* basicLightShader();

	private:
		static const char* default_shader_vert;
		static const char* default_shader_frag;

		static const char* basic_light_shader_vert;
		static const char* basic_light_shader_frag;
	};
}