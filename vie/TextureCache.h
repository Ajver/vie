#pragma once

#include <map>

namespace vie
{
	class Texture;

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Texture getTexture(std::string);

	private:
		std::map<std::string, Texture> textureMap;
	};

}