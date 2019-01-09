#pragma once

#include "WindowFlags.h"

#include <SDL/SDL.h>

namespace vie
{

	class Window
	{
	public:

		static void create(const char* title, unsigned int sw, unsigned int sh, WindowFlags wFlags);

		static void setWindowSize(unsigned int sw, unsigned int sh);
		static void setWindowTitle(const char* title);

		static SDL_GLContext getSDLGLContext();
		static void swapSDLWindowBuffer();
		static void destroySDLWindow();

		static unsigned int getScreenWidth();
		static unsigned int getScreenHeight();

		static bool isWindowInvisible();
		static bool isWindowFullscreen();
		static bool isWindowBorderless();
		static bool isWindowResizable();

	private:
		static SDL_Window* sdlWindow;
		static const char* windowTitle;
		static unsigned int screenWidth;
		static unsigned int screenHeight;
		static WindowFlags windowFlags;

		static void saveWindowProperties(const char* title, unsigned int sw, unsigned int sh, WindowFlags wFlags);
		static void createSDLWindow();
		static Uint32 getSDLWindowFlags();
		static void updateScreenSize();
		static void updateWindowTitle();
		static void catchErrors();
	};

}
