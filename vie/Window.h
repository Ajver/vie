#pragma once

#include "WindowFlags.h"

#include <SDL/SDL.h>

namespace vie
{

	class Window
	{
	public:
		Window();

		void create(const char* title, unsigned int sw, unsigned int sh, WindowFlags wFlags);

		void setWindowSize(unsigned int sw, unsigned int sh);
		void setWindowTitle(const char* title);

		SDL_GLContext getSDLGLContext();
		void swapSDLWindowBuffer();
		void destroySDLWindow();

		unsigned int getScreenWidth();
		unsigned int getScreenHeight();

		bool isWindowInvisible();
		bool isWindowFullscreen();
		bool isWindowBorderless();
		bool isWindowResizable();

	private:
		SDL_Window* sdlWindow;
		const char* windowTitle;
		unsigned int screenWidth;
		unsigned int screenHeight;
		WindowFlags windowFlags;

		void saveWindowProperties(const char* title, unsigned int sw, unsigned int sh, WindowFlags wFlags);
		void createSDLWindow();
		Uint32 getSDLWindowFlags();
		void updateScreenSize();
		void updateWindowTitle();
		void catchErrors();
	};

}
