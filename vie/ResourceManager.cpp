#include "ResourceManager.h"

#include "Texture.h"
#include "TextureCache.h"

namespace vie
{

	TextureCache ResourceManager::textureCache;

	Texture ResourceManager::getTexture(std::string texturePath)
	{
		return ResourceManager::textureCache.getTexture(texturePath);
	}

}