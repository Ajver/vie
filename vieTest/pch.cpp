//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include <SDL/SDL.h>

int main(int argc, char *args[])
{
	testing::InitGoogleTest(&argc, args);

	return RUN_ALL_TESTS();
}