#include "ResourceManager.h"

#include <vector>

#include "IOManager.h"
#include "Errors.h"


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
			Texture newTexture = loadPNG(texturePath);

			// Add new texture to the map for future
			texturesMap.insert(make_pair(texturePath, newTexture));
			
			return newTexture;
		}

		// If texture was found - return it!
		return mit->second;
	}

	Texture ResourceManager::loadPNG(std::string filePath)
	{
		Texture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width;
		unsigned long height;

		if (!IOManager::readFileToBuffer(filePath, in))
		{
			fatalError("Failed to load PNG file to buffer: " + filePath);
		}

		int errorCode = IOManager::decodePNG(out, width, height, &(in[0]), in.size());

		// 0 - no error
		if (errorCode != 0)
		{
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_MIPMAP);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		// Return a copy of texture data
		return texture;
	}

}