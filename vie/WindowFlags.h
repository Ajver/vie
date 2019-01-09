#pragma once

namespace vie
{

	enum WindowFlags : unsigned int
	{
		// Noresizable, visible window
		DEFAULT = 0x0,

		// Window invisible
		INVISIBLE = 0x1,

		// Borderless and fillign the screen
		FULLSCREEN = 0x2,

		// Noresizable
		BORDERLESS = 0x4,

		// Resizable, with border
		RESIZABLE = 0x8
	};

}
