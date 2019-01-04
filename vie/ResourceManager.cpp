#include "ResourceManager.h"

#include "ImageLoader.h"

namespace vie
{
	std::map<std::string, Texture> ResourceManager::texturesMap;

	Texture ResourceManager::getTexture(std::string texturePath)
	{
		// Lookup the texture and see if its in the map
		auto mit = texturesMap.find(texturePath);

		// If it's not in the map
		if (mit == texturesMap.end()) {
			// Load the texture
			Texture newTexture = ImageLoader::loadPNG(texturePath);

			// Add new texture to the map for future
			texturesMap.insert(make_pair(texturePath, newTexture));
			
			return newTexture;
		}

		// If texture was found - return it!
		return mit->second;
	}

}