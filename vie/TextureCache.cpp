#include "TextureCache.h"
#include "ImageLoader.h"
#include "Texture.h"

#include <iostream>

namespace vie
{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::getTexture(std::string texturePath)
	{
		// Lookup the texture and see if its in the map
		auto mit = textureMap.find(texturePath);

		// If it's not in the map
		if (mit == textureMap.end()) {
			// Load the texture
			Texture newTexture = ImageLoader::loadPNG(texturePath);

			textureMap.insert(make_pair(texturePath, newTexture));

			//std::cout << "Loaded new texture: " << texturePath << std::endl;

			return newTexture;
		}

		//std::cout << "Used cached texture: " << texturePath << std::endl;

		// If texture was found - return it!
		return mit->second;
	}

}