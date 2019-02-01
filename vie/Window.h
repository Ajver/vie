#pragma once

#include "WindowFlags.h"

#include <glm/glm.hpp>
#include <SDL/SDL.h>

namespace vie
{

	class Window
	{
	public:
		static void create(const char* title, int sw, int sh, WindowFlags wFlags);

		static void setWindowSize(int sw, int sh);
		static void setWindowTitle(const char* title);

		static SDL_GLContext getSDLGLContext();
		static void swapSDLWindowBuffer();
		static void destroySDLWindow();

		static glm::vec2 getScreenSize();
		static int getScreenWidth();
		static int getScreenHeight();

		static bool isWindowInvisible();
		static bool isWindowFullscreen();
		static bool isWindowBorderless();
		static bool isWindowResizable();

		static void updateScreenSizeFromSDL();

	private:
		static SDL_Window* sdlWindow;
		static const char* windowTitle;
		static int screenWidth;
		static int screenHeight;
		static WindowFlags windowFlags;

		static void saveWindowProperties(const char* title, int sw, int sh, WindowFlags wFlags);
		static void createSDLWindow();
		static Uint32 getSDLWindowFlags();
		static const char* getWindowTitle();
		static void updateWindowTitleFromSDL();
		static void catchErrors();
	};

}
