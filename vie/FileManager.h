#pragma once

#include <vector>
#include <map>

#include "Texture.h"

namespace vie
{

	class FileManager
	{
	public:
		static Texture getTexture(const std::string& texturePath);
		static Texture reloadTexture(const std::string& texturePath);

	private:
		static std::map<std::string, Texture> texturesMap;

		static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
		static Texture loadPNG(const std::string& filePath);
		static int decodePNG(std::vector<unsigned char>&, unsigned long&, unsigned long&, const unsigned char*, size_t, bool = true);
	};

}

