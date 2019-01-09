#include "Window.h"

#include "Errors.h"

namespace vie
{

	Window::Window() : 
		sdlWindow(nullptr),
		screenWidth(0),
		screenHeight(0)
	{
	}

	void Window::create(const char* title, unsigned int sw, unsigned int sh, WindowFlags wFlags)
	{
		saveWindowProperties(title, sw, sh, wFlags);

		createSDLWindow();

		if (sdlWindow == nullptr)
		{
			fatalError(SDL_GetError());
		}
	}

	void Window::setWindowSize(unsigned int sw, unsigned int sh)
	{
		screenWidth = sw;
		screenHeight = sh;
		updateScreenSize();
	}

	void Window::setWindowTitle(const char* title)
	{
		windowTitle = title;
	}

	SDL_GLContext Window::getSDLGLContext()
	{
		return SDL_GL_CreateContext(sdlWindow);
	}

	void Window::swapSDLWindowBuffer()
	{
		SDL_GL_SwapWindow(sdlWindow);
	}

	void Window::destroySDLWindow()
	{
		SDL_DestroyWindow(sdlWindow);
	}

	unsigned int Window::getScreenWidth()
	{
		return screenWidth;
	}

	unsigned int Window::getScreenHeight()
	{
		return screenHeight;
	}

	bool Window::isWindowInvisible()
	{
		return windowFlags & WindowFlags::INVISIBLE;
	}

	bool Window::isWindowFullscreen()
	{
		return windowFlags & WindowFlags::FULLSCREEN;
	}

	bool Window::isWindowBorderless()
	{
		return windowFlags & WindowFlags::BORDERLESS;
	}

	bool Window::isWindowResizable()
	{
		return windowFlags & WindowFlags::RESIZABLE;
	}

	void Window::saveWindowProperties(const char* title, unsigned int sw, unsigned int sh, WindowFlags wFlags)
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

	void Window::updateScreenSize()
	{
		SDL_SetWindowSize(sdlWindow, screenWidth, screenHeight);
	}

	void Window::updateWindowTitle()
	{
		SDL_SetWindowTitle(sdlWindow, windowTitle);
	}
}