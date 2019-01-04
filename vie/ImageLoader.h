#pragma once

#include <string>

namespace vie
{
	class Texture;

	class ImageLoader
	{
	public:

		static Texture loadPNG(std::string);
	};

}

