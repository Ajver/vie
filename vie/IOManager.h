#pragma once

#include <vector>

namespace vie
{

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string, std::vector<unsigned char> &);
		static int decodePNG(std::vector<unsigned char>&, unsigned long&, unsigned long&, const unsigned char*, size_t, bool = true);		
	};
}

