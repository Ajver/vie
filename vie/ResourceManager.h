#pragma once

#include <string>

namespace vie
{
	class Texture;
	class TextureCache;

	class ResourceManager
	{
	public:
		static Texture getTexture(std::string);

	private:
		static TextureCache textureCache;
	};
}

