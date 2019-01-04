#pragma once

#include <vector>

namespace vie
{

	extern int decodePNG(std::vector<unsigned char>&, unsigned long&, unsigned long&, const unsigned char*, size_t, bool = true);

}