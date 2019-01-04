#pragma once

#include <vector>
#include <map>

#include "Texture.h"

namespace vie
{

	class ResourceManager
	{
	public:
		static Texture getTexture(std::string filePath);

	private:
		static std::map<std::string, Texture> texturesMap;

		static Texture loadPNG(std::string filePath); 
		static bool readFileToBuffer(std::string, std::vector<unsigned char> &);
		static int decodePNG(std::vector<unsigned char>&, unsigned long&, unsigned long&, const unsigned char*, size_t, bool = true);
	};

}

