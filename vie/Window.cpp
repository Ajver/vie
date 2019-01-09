#include "Window.h"

#include "Errors.h"

namespace vie
{
	SDL_Window* Window::sdlWindow;
	const char* Window::windowTitle;
	int Window::screenWidth;
	int Window::screenHeight;
	WindowFlags Window::windowFlags;

	void Window::create(const char* title, int sw, int sh, WindowFlags wFlags)
	{
		saveWindowProperties(title, sw, sh, wFlags);
		createSDLWindow();
		catchErrors();
	}

	void Window::saveWindowProperties(const char* title, int sw, int sh, WindowFlags wFlags)
	{
		windowTitle = title;
		screenWidth = sw;
		screenHeight = sh;
		windowFlags = wFlags;
	}

	void Window::createSDLWindow()
	{
		Uint32 sdlFlags = getSDLWindowFlags();
		sdlWindow = SDL_CreateWindow(
			windowTitle,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			screenWidth,
			screenHeight,
			sdlFlags);
	}

	Uint32 Window::getSDLWindowFlags()
	{
		Uint32 sdlFlags = SDL_WINDOW_OPENGL;

		if (isWindowInvisible())
			sdlFlags |= SDL_WINDOW_HIDDEN;

		if (isWindowFullscreen())
			sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		if (isWindowBorderless())
			sdlFlags |= SDL_WINDOW_BORDERLESS;

		if (isWindowResizable())
			sdlFlags |= SDL_WINDOW_RESIZABLE;

		return sdlFlags;
	}

	bool Window::isWindowInvisible()
	{ return windowFlags & WindowFlags::INVISIBLE; }

	bool Window::isWindowFullscreen()
	{ return windowFlags & WindowFlags::FULLSCREEN; }

	bool Window::isWindowBorderless()
	{ return windowFlags & WindowFlags::BORDERLESS; }

	bool Window::isWindowResizable()
	{ return windowFlags & WindowFlags::RESIZABLE; }

	void Window::catchErrors()
	{
		if (sdlWindow == nullptr)
			fatalError(SDL_GetError());
	}

	void Window::setWindowSize(int sw, int sh)
	{
		screenWidth = sw;
		screenHeight = sh;
		SDL_SetWindowSize(sdlWindow, screenWidth, screenHeight);
	}

	void Window::setWindowTitle(const char* title)
	{ 
		windowTitle = title; 
		SDL_SetWindowTitle(sdlWindow, windowTitle);
	}
	
	const char* Window::getWindowTitle()
	{
		updateWindowTitleFromSDL();
		return windowTitle;
	}

	void Window::updateWindowTitleFromSDL()
	{ windowTitle = SDL_GetWindowTitle(sdlWindow); }

	SDL_GLContext Window::getSDLGLContext()
	{ return SDL_GL_CreateContext(sdlWindow); }

	void Window::swapSDLWindowBuffer()
	{ SDL_GL_SwapWindow(sdlWindow); }

	void Window::destroySDLWindow()
	{ SDL_DestroyWindow(sdlWindow); }

	int Window::getScreenWidth()
	{
		return screenWidth; 
	}

	int Window::getScreenHeight()
	{
		return screenHeight; 
	}

	void Window::updateScreenSizeFromSDL()
	{ SDL_GetWindowSize(sdlWindow, (int*)&screenWidth, (int*)&screenHeight); }

}