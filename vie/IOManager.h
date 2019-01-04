#pragma once

#include <vector>
#include <map>

#include "Texture.h"

namespace vie
{

	class IOManager
	{
	public:
		static Texture getTexture(std::string filePath);

	private:
		static std::map<std::string, Texture> texturesMap;

		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static Texture loadPNG(std::string filePath); 
		static int decodePNG(std::vector<unsigned char>&, unsigned long&, unsigned long&, const unsigned char*, size_t, bool = true);
	};

}

