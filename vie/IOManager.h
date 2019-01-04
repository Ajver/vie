#pragma once

#include <vector>

namespace vie
{

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string, std::vector<unsigned char> &);
	};
}

