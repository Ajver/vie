#pragma once

#include <string>
#include <map>

#include "Texture.h"

namespace vie
{

	class ResourceManager
	{
	public:
		static Texture getTexture(std::string);

	private:
		static std::map<std::string, Texture> texturesMap;
	};

}

